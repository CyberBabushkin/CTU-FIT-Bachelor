#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cassert>
using namespace std;

#define SECTOR_SIZE                      16
#define MAX_RAID_DEVICES                 16
#define MAX_DEVICE_SECTORS (1024 * 1024 * 2)
#define MIN_DEVICE_SECTORS (   1 * 1024 * 2)

#define RAID_OK                           0
#define RAID_DEGRADED                     1
#define RAID_FAILED                       2
#define RAID_STOPPED                      3

struct TBlkDev
{
    int              m_Devices;
    int              m_Sectors;
    int           (* m_Read )  ( int, int, void *, int );
    int           (* m_Write ) ( int, int, const void *, int );
};

#endif /* __PROGTEST__ */

// #################################################################################################### //
// ############################################## STRUCTURES ########################################## //

#define DEVS  	(mainRaid.config.m_Devices)

struct RaidConfig {
    RaidConfig() : config(),
                   version(0),
                   loaded(false),
                   status(RAID_STOPPED),
                   failedDrive(-1) {}

    TBlkDev					config;
    int                     version;
    bool					loaded;
    int 					status;
    int 					failedDrive;


    bool operator== (const RaidConfig & a) {
        return this->version == a.version &&
               this->loaded == a.loaded &&
               this->status == a.status &&
               this->failedDrive == a.failedDrive;

    }

    bool operator!= (const RaidConfig & a) {
        return ! operator==(a);
    }
};

// ---------------------------------------------------------------------------------------------------- //

struct Overhead {
    Overhead() : version(0),
                 failedDrive(-1) {}

    int						version;
    int                     failedDrive;
    int 					status;

    bool operator== (const Overhead & a) {
        return this->version == a.version &&
               this->failedDrive == a.failedDrive &&
               this->status == a.status;
    }

    bool operator!= (const Overhead & a) {
        return ! operator==(a);
    }
};

// ---------------------------------------------------------------------------------------------------- //

struct OverheadLoading
{
    Overhead 	head;
    bool		loaded;
};

// #################################################################################################### //
// ########################################### GLOBAL VARIABLES ####################################### //

RaidConfig mainRaid;

// #################################################################################################### //
// ######################################### ADDITIONAL FUNCTIONS ##################################### //

void parityXOR(unsigned char * buffer, unsigned char * a, unsigned char * b, int size) {
    for (int i = 0; i < size; i++) {
        buffer[i] = a[i] ^ b[i];
    }
}

// ---------------------------------------------------------------------------------------------------- //

int overheadSize() {
    return (sizeof(Overhead) % (SECTOR_SIZE)) == 0 ?
           (sizeof(Overhead) / SECTOR_SIZE) :
           (sizeof(Overhead) / SECTOR_SIZE) + 1;
}

// ---------------------------------------------------------------------------------------------------- //

int getParitySectorForLine(int line) {
    return line % DEVS;
}

// ---------------------------------------------------------------------------------------------------- //

int getStartingLine(int sectorNumber) {
    return sectorNumber / (DEVS - 1);
}

// ---------------------------------------------------------------------------------------------------- //

int getStartingSector(int sectorNumber) {
    int startingLine = getStartingLine(sectorNumber);
    int sectorPosInLine = sectorNumber - (startingLine * (DEVS - 1));
    int parity = getParitySectorForLine(startingLine);

    return sectorPosInLine >= parity ? sectorPosInLine + 1 : sectorPosInLine;
}

// ---------------------------------------------------------------------------------------------------- //

Overhead createHeader() {
    Overhead h = Overhead();
    h.version = mainRaid.version;
    h.failedDrive = mainRaid.failedDrive;
    h.status = mainRaid.status;
    return h;
}

// ---------------------------------------------------------------------------------------------------- //

void writeHeader(int i) {
    if (i == mainRaid.failedDrive)
        return;

    int size = overheadSize();
    unsigned char * buf = new unsigned char[size * SECTOR_SIZE];
    memset(buf, 0, size * SECTOR_SIZE);

    Overhead head = createHeader();

    memcpy(buf, &head, sizeof(Overhead));

    int r = mainRaid.config.m_Write(i, 0, buf, size);

    if (r != size) {
        mainRaid.failedDrive = i;
        mainRaid.status = (mainRaid.status == RAID_DEGRADED || mainRaid.status == RAID_FAILED) ?
                          RAID_FAILED :
                          RAID_DEGRADED;
        head = createHeader();
        memcpy(buf, &head, sizeof(Overhead));
        for (int j = 0; j < i; j++) mainRaid.config.m_Write(j, 0, buf, size);
    }

    delete [] buf;
}

// ---------------------------------------------------------------------------------------------------- //

void writeHeaders() {
    for (int i = 0; i < DEVS; i++) {
        writeHeader(i);
    }
}

// ---------------------------------------------------------------------------------------------------- //

OverheadLoading loadHeaderFromDisk(int device) {
    int size = overheadSize();
    unsigned char * buf = new unsigned char[size * SECTOR_SIZE];
    memset(buf, 0, size * SECTOR_SIZE);
    int read = mainRaid.config.m_Read(device, 0, buf, size);

    OverheadLoading load;
    load.loaded = true;

    if (read != overheadSize()) {
        load.loaded = false;
    }

    load.head = *((Overhead*) buf);

    delete [] buf;
    return load;
}

// ---------------------------------------------------------------------------------------------------- //

void loadAllHeadersFromDisks() {
    Overhead correctOverhead;
    Overhead first;
    Overhead second;
    int votes1 = 0;
    int votes2 = 0;
    int drive1 = -1;
    int drive2 = -1;

    int votesUnread = 0;
    int unread = -1;

    for (int i = 0; i < DEVS; i++) {

        OverheadLoading loadedHeader = loadHeaderFromDisk(i);

        if (! loadedHeader.loaded) {
            if (votesUnread > 0) {
                mainRaid.status = RAID_FAILED;
                return;
            }

            unread = i;
            ++ votesUnread;

        } else {
            Overhead oh = loadedHeader.head;

            if (votes1 == 0) {
                first = oh;
                votes1++;
                drive1 = i;
            } else if (oh != first) {
                if (votes2 != 0 && second != oh) {
                    mainRaid.status = RAID_FAILED;
                    return;
                }

                second = oh;
                votes2++;
                drive2 = i;

            } else {
                votes1++;
                drive1 = i;
            }
        }
    }

    if (votesUnread == 0) {
        if (votes2 > votes1) {
            mainRaid.failedDrive = drive1;
            correctOverhead = second;
        } else if (votes2 < votes1) {
            mainRaid.failedDrive = drive2;
            correctOverhead = first;
        } else {
            mainRaid.status = RAID_FAILED;
            return;
        }
    } else {
        if (votes1 > 0 && votes2 > 0) {
            mainRaid.status = RAID_FAILED;
            return;
        }

        mainRaid.failedDrive = unread;

        if (votes1 == 0) {
            correctOverhead = second;
        }

        if (votes2 == 0) {
            correctOverhead = first;
        }
    }

    if (correctOverhead.failedDrive != mainRaid.failedDrive) {
        mainRaid.status = RAID_FAILED;
        return;
    }

    if (correctOverhead.status == RAID_FAILED) {
        mainRaid.status = RAID_FAILED;
        mainRaid.failedDrive = correctOverhead.failedDrive;
    }

    if (correctOverhead.failedDrive != -1 && correctOverhead.status != RAID_FAILED) {
        mainRaid.status = RAID_DEGRADED;
        mainRaid.failedDrive = correctOverhead.failedDrive;
    }

    mainRaid.version = correctOverhead.version + 1;
}

// ---------------------------------------------------------------------------------------------------- //

int setupRAIDOnError(int brokenDev) {
    if (mainRaid.status == RAID_DEGRADED) {
        mainRaid.status = RAID_FAILED;
        return RAID_FAILED;
    }
    mainRaid.status = RAID_DEGRADED;
    mainRaid.failedDrive = brokenDev;
    return RAID_DEGRADED;
}

// ---------------------------------------------------------------------------------------------------- //

bool repairBrokenSector(unsigned char * brokenSector, int drive, int cacheLine) {
    int size = overheadSize();
    int line = size + cacheLine;

    unsigned char buf[SECTOR_SIZE];
    memset(brokenSector, 0, SECTOR_SIZE);

    for (int i = 0; i < DEVS; i++) {
        if (i == drive) continue;

        int r = mainRaid.config.m_Read(i, line, buf, 1);

        if (r != 1) {
            return false;
        }

        parityXOR(brokenSector, brokenSector, buf, SECTOR_SIZE);
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------- //

int computeXORFromPositionToPosition(unsigned char * xorSector, unsigned char * brokenSector, int from, int to, int line) {
    int headerSize = overheadSize();
    int parity = getParitySectorForLine(line);

    unsigned char buffer[SECTOR_SIZE];

    for (int i = from; i < to; i++) {
        if (i == parity) continue;

        if (i == mainRaid.failedDrive) {
            parityXOR(xorSector, xorSector, brokenSector, SECTOR_SIZE);
            continue;
        }

        int r = mainRaid.config.m_Read(i, line + headerSize, buffer, 1);

        if (r != 1) {
            if (setupRAIDOnError(i) == RAID_FAILED) return 0;
            bool suc = repairBrokenSector(brokenSector, mainRaid.failedDrive, line);
            if (! suc) {
                mainRaid.status = RAID_FAILED;
                return 0;
            }
            parityXOR(xorSector, xorSector, brokenSector, SECTOR_SIZE);
            continue;
        }

        parityXOR(xorSector, xorSector, buffer, SECTOR_SIZE);
    }

    return 1;
}

// #################################################################################################### //
// ############################################ RAID FUNCTIONS ######################################## //

int                RaidCreate                              ( TBlkDev         * dev ) {
    if (dev == NULL)
        return 0;

    mainRaid = RaidConfig();
    mainRaid.config = TBlkDev();
    mainRaid.config.m_Sectors = dev->m_Sectors;
    mainRaid.config.m_Devices = dev->m_Devices;
    mainRaid.config.m_Read = dev->m_Read;
    mainRaid.config.m_Write = dev->m_Write;

    if ((mainRaid.config.m_Devices < 3) ||
        (mainRaid.config.m_Devices > MAX_RAID_DEVICES) ||
        (mainRaid.config.m_Sectors < MIN_DEVICE_SECTORS) ||
        (mainRaid.config.m_Sectors > MAX_DEVICE_SECTORS)) {
        mainRaid = RaidConfig();
        return 0;
    }

    writeHeaders();
    return mainRaid.status != RAID_FAILED;
}

// ---------------------------------------------------------------------------------------------------- //

void               RaidStart                               ( TBlkDev         * dev ) {
    if (dev == NULL)
        return;

    mainRaid = RaidConfig();
    mainRaid.config = *dev;
    loadAllHeadersFromDisks();
    mainRaid.loaded = true;

    if (mainRaid.status == RAID_STOPPED)
        mainRaid.status = RAID_OK;

    ++ mainRaid.version;
    writeHeaders();
}

// ---------------------------------------------------------------------------------------------------- //

void               RaidStop                                ( void ) {
    if (mainRaid.loaded) {
        mainRaid.version++;
        if (mainRaid.status == RAID_OK) mainRaid.status = RAID_STOPPED;
        writeHeaders();
        mainRaid = RaidConfig();
    }
}

// ---------------------------------------------------------------------------------------------------- //

int                RaidStatus                              ( void ) {
    if (! mainRaid.loaded)
        return RAID_STOPPED;

    return mainRaid.status;
}

// ---------------------------------------------------------------------------------------------------- //

int                RaidSize                                ( void ) {
    if (! mainRaid.loaded)
        return 0;

    return (DEVS - 1) * (mainRaid.config.m_Sectors - overheadSize());
}

// ---------------------------------------------------------------------------------------------------- //

int                RaidRead                                ( int               sector,
                                                             void            * data,
                                                             int               sectorCnt ) {

    if (! mainRaid.loaded || mainRaid.status == RAID_STOPPED || mainRaid.status == RAID_FAILED)
        return 0;

    int total = 0;

    int startingLine = getStartingLine(sector);
    int startingPosition = getStartingSector(sector);
    int parity = getParitySectorForLine(startingLine);
    int linesCount = getStartingLine(sector + sectorCnt - 1) - getStartingLine(sector) + 1;

    unsigned char brokenSector[SECTOR_SIZE];
    memset(brokenSector, 0, SECTOR_SIZE);

    unsigned char * dataChar = (unsigned char *) data;

    for (int line = startingLine; line < linesCount + startingLine; ++ line) {
        int from = line == startingLine ? startingPosition : 0;
        int to = line == linesCount + startingLine - 1 ? getStartingSector(sector + sectorCnt - 1) : DEVS - 1;
//        if (to == 0 || to <= from) to = DEVS; // the last sector

        if (mainRaid.failedDrive != -1) {
            bool suc = repairBrokenSector(brokenSector, mainRaid.failedDrive, line);
            if (! suc) {
                return 0;
            }
        }

        for (int pos = from; pos <= to; ++ pos) {
            if (pos == parity) continue;

            if (pos == mainRaid.failedDrive) {
                for (int i = 0; i < SECTOR_SIZE; ++ i) {
                    dataChar[total * SECTOR_SIZE + i] = brokenSector[i];
                }
                ++ total;
                continue;
            }

            int r = mainRaid.config.m_Read(pos, overheadSize() + line, (void*) (dataChar + total * SECTOR_SIZE), 1);
            ++ total;

            if (r != 1) {
                if (setupRAIDOnError(pos) == RAID_FAILED) {
                    return total;
                }

                bool suc = repairBrokenSector(brokenSector, mainRaid.failedDrive, line);
                if (! suc) {
                    return total;
                }

                for (int i = 0; i < SECTOR_SIZE; ++ i) {
                    dataChar[total * SECTOR_SIZE + i] = brokenSector[i];
                }
            }
        }

        parity = (parity + 1) % DEVS;
    }

    return total;
}

// ---------------------------------------------------------------------------------------------------- //

int                RaidWrite                               ( int               sector,
                                                             const void      * data,
                                                             int               sectorCnt ) {
    if (! mainRaid.loaded || mainRaid.status == RAID_STOPPED || mainRaid.status == RAID_FAILED)
        return 0;

    int total = 0;
    int startingLine = getStartingLine(sector);
    int startingPosition = getStartingSector(sector);
    int parity = getParitySectorForLine(startingLine);
    int linesCount = getStartingLine(sector + sectorCnt - 1) - getStartingLine(sector) + 1;

    unsigned char xorSector[SECTOR_SIZE];
    unsigned char brokenSector[SECTOR_SIZE];
    memset(brokenSector, 0, SECTOR_SIZE);

    unsigned char * dataChar = (unsigned char *) data;

    for (int line = startingLine; line < linesCount + startingLine; ++ line) {
        int from = line == startingLine ? startingPosition : 0;
        int to = line == linesCount + startingLine - 1 ? getStartingSector(sector + sectorCnt - 1) : DEVS - 1;

        memset(xorSector, 0, SECTOR_SIZE);

        if (mainRaid.failedDrive != -1 && (from > 0 || to < DEVS - 1)) {
            bool suc = repairBrokenSector(brokenSector, mainRaid.failedDrive, line);
            if (! suc) {
                return 0;
            }
        }

        if (from > 0) computeXORFromPositionToPosition(xorSector, brokenSector, 0, from, line);
        if (to < DEVS - 1) computeXORFromPositionToPosition(xorSector, brokenSector, to + 1, DEVS, line);

        for (int pos = from; pos <= to; ++ pos) {
            if (pos == parity) continue;

            parityXOR(xorSector, xorSector, dataChar + total * SECTOR_SIZE, SECTOR_SIZE);

            if (pos == mainRaid.failedDrive) { ++ total; continue; }

            unsigned char * dataToWrite = dataChar + total * SECTOR_SIZE;
            int r = mainRaid.config.m_Write(pos, overheadSize() + line, (void*) dataToWrite, 1);
            ++ total;

            if (r != 1) {
                if (setupRAIDOnError(pos) == RAID_FAILED) {
                    return total;
                }
            }
        }

        if (mainRaid.failedDrive != parity) {
            int r = mainRaid.config.m_Write(parity, overheadSize() + line, (void*) xorSector, 1);

            if (r != 1) {
                if (setupRAIDOnError(parity) == RAID_FAILED) {
                    return total;
                }
            }
        }

        parity = (parity + 1) % DEVS;
    }


    return total;
}

// ---------------------------------------------------------------------------------------------------- //

int                RaidResync                              ( void ) {
    if (mainRaid.status == RAID_OK) return 1;
    if (mainRaid.status == RAID_STOPPED || mainRaid.status == RAID_FAILED) return 0;

    int f = mainRaid.failedDrive;

    unsigned char brokenSector[SECTOR_SIZE];
    memset(brokenSector, 0, SECTOR_SIZE);

    int linesCount = mainRaid.config.m_Sectors - overheadSize();
    bool written = true;

    for (int line = overheadSize(); line < linesCount; ++ line) {
        bool suc = repairBrokenSector(brokenSector, mainRaid.failedDrive, line - overheadSize());

        if (! suc) {
            mainRaid.status = RAID_FAILED;
            break;
        }

        int r = mainRaid.config.m_Write(mainRaid.failedDrive, line, brokenSector, 1);

        if (r != 1) {
            written = false;
            break;
        }
    }

    if (mainRaid.status == RAID_FAILED) {
        mainRaid.version++;
        writeHeaders();
        return 0;
    }

    if (written) {
        mainRaid.status = RAID_OK;
        mainRaid.failedDrive = -1;
    }

    mainRaid.version++;
    writeHeaders();

    if (mainRaid.status == RAID_FAILED ||
            (mainRaid.status == RAID_DEGRADED && f != mainRaid.failedDrive)) {
        mainRaid.status = RAID_FAILED;
        mainRaid.version++;
        writeHeaders();
        return 0;
    }

    return mainRaid.status == RAID_OK;
}

// #################################################################################################### //
// #################################################################################################### //

#ifndef __PROGTEST__
//#include "tests.inc"

/* SW RAID5 - basic test
 *
 * The testing of the RAID driver requires a backend (simulating the underlying disks).
 * Next, the tests of your RAID implemetnation are needed. To help you with the implementation,
 * a sample backend is implemented in this file. It provides a quick-and-dirty
 * implementation of the underlying disks (simulated in files) and a few Raid... function calls.
 *
 * The implementation in the real testing environment is different. The sample below is a
 * minimalistic disk backend which matches the required interface. The backend, for instance,
 * cannot simulate a crashed disk. To test your Raid implementation, you will have to modify
 * or extend the backend.
 *
 * Next, you will have to add some raid testing. There is a few Raid... functions called from within
 * main(), however, the tests are incomplete. For instance, RaidResync () is not tested here. Once
 * again, this is only a starting point.
 */

#define RAID_DEVICES 4
#define DISK_SECTORS 8192

static FILE  * g_Fp[RAID_DEVICES];
static bool flag = true;
static bool flag1 = false;

//-------------------------------------------------------------------------------------------------
/** Sample sector reading function. The function will be called by your Raid driver implementation.
 * Notice, the function is not called directly. Instead, the function will be invoked indirectly
 * through function pointer in the TBlkDev structure.
 */
int                diskRead                                ( int               device,
                                                             int               sectorNr,
                                                             void            * data,
                                                             int               sectorCnt )
{
    if (device == 1 && flag) return 0;
    if (device == 2 && flag1) return 0;

    if ( device < 0 || device >= RAID_DEVICES )
        return 0;
    if ( g_Fp[device] == NULL )
        return 0;
    if ( sectorCnt <= 0 || sectorNr + sectorCnt > DISK_SECTORS )
        return 0;
    fseek ( g_Fp[device], sectorNr * SECTOR_SIZE, SEEK_SET );
    return fread ( data, SECTOR_SIZE, sectorCnt, g_Fp[device] );
}
//-------------------------------------------------------------------------------------------------
/** Sample sector writing function. Similar to diskRead
 */
int                diskWrite                               ( int               device,
                                                             int               sectorNr,
                                                             const void      * data,
                                                             int               sectorCnt )
{
    if (device == 1 && flag) return 0;
    if (device == 2 && flag1) return 0;

    if ( device < 0 || device >= RAID_DEVICES )
        return 0;
    if ( g_Fp[device] == NULL )
        return 0;
    if ( sectorCnt <= 0 || sectorNr + sectorCnt > DISK_SECTORS )
        return 0;
    fseek ( g_Fp[device], sectorNr * SECTOR_SIZE, SEEK_SET );
    return fwrite ( data, SECTOR_SIZE, sectorCnt, g_Fp[device] );
}
//-------------------------------------------------------------------------------------------------
/** A function which releases resources allocated by openDisks/createDisks
 */
void               doneDisks                               ( TBlkDev         * dev )
{
    delete dev;
    for ( int i = 0; i < RAID_DEVICES; i ++ )
        if ( g_Fp[i] )
        {
            fclose ( g_Fp[i] );
            g_Fp[i]  = NULL;
        }
}
//-------------------------------------------------------------------------------------------------
/** A function which creates the files needed for the sector reading/writing functions above.
 * This function is only needed for the particular implementation above.
 */
TBlkDev          * createDisks                             ( void )
{
    char       buffer[SECTOR_SIZE];
    TBlkDev  * res = NULL;
    char       fn[100];

    memset    ( buffer, 0, sizeof ( buffer ) );

    for ( int i = 0; i < RAID_DEVICES; i ++ )
    {
        snprintf ( fn, sizeof ( fn ), "/tmp/%04d", i );
        g_Fp[i] = fopen ( fn, "w+b" );

        if ( ! g_Fp[i] )
        {
            doneDisks ( NULL );
            return NULL;
        }

        for ( int j = 0; j < DISK_SECTORS; j ++ )
            if ( fwrite ( buffer, sizeof ( buffer ), 1, g_Fp[i] ) != 1 )
            {
                doneDisks ( NULL );
                return NULL;
            }
    }

    res              = new TBlkDev;
    res -> m_Devices = RAID_DEVICES;
    res -> m_Sectors = DISK_SECTORS;
    res -> m_Read    = diskRead;
    res -> m_Write   = diskWrite;
    return res;
}
//-------------------------------------------------------------------------------------------------
/** A function which opens the files needed for the sector reading/writing functions above.
 * This function is only needed for the particular implementation above.
 */
TBlkDev          * openDisks                               ( void )
{
    TBlkDev  * res = NULL;
    char       fn[100];

    for ( int i = 0; i < RAID_DEVICES; i ++ )
    {
        snprintf ( fn, sizeof ( fn ), "/tmp/%04d", i );
        g_Fp[i] = fopen ( fn, "r+b" );
        if ( ! g_Fp[i] )
        {
            doneDisks ( NULL );
            return NULL;
        }
        fseek ( g_Fp[i], 0, SEEK_END );
        if ( ftell ( g_Fp[i] ) != DISK_SECTORS * SECTOR_SIZE )
        {
            doneDisks ( NULL );
            return NULL;
        }
    }

    res              = new TBlkDev;
    res -> m_Devices = RAID_DEVICES;
    res -> m_Sectors = DISK_SECTORS;
    res -> m_Read    = diskRead;
    res -> m_Write   = diskWrite;
    return res;
}
//-------------------------------------------------------------------------------------------------
int main ( void )
{
    unsigned char buffer[SECTOR_SIZE];

    TBlkDev * dev = createDisks();
    assert(RaidCreate(dev));
    RaidStart(dev);

    assert(RaidStatus() == RAID_DEGRADED);
    assert(RaidWrite(0, buffer, 1) == 1);
    assert(RaidWrite(1, buffer, 1) == 1);
    assert(RaidWrite(2, buffer, 1) == 1);

    RaidStop();
    RaidStart(dev);

    flag = false;

    assert(RaidResync() == 1);
    assert(RaidStatus() == RAID_OK);
    assert(RaidWrite(0, buffer, 1) == 1);
    assert(RaidWrite(1, buffer, 1) == 1);
    assert(RaidWrite(2, buffer, 1) == 1);

    RaidStop();

    flag = false;
    flag1 = false;

    RaidStart(dev);
    assert(RaidStatus() == RAID_OK);
    assert(RaidWrite(0, buffer, 1) == 1);
    assert(RaidWrite(1, buffer, 1) == 1);
    flag1 = true;
    assert(RaidWrite(2, buffer, 1) == 1);
    assert(RaidStatus() == RAID_DEGRADED);

    RaidStop();

    flag1 = false;
    RaidStart(dev);
    assert(RaidResync() == 1);
    assert(RaidStatus() == RAID_OK);

    flag1 = true;
    assert(RaidWrite(1, buffer, 1) == 1);
    assert(RaidStatus() == RAID_DEGRADED);
    flag = true;
    flag1 = false;
    assert(RaidResync() == 0);
    assert(RaidStatus() == RAID_FAILED);
    RaidStop();
    RaidStart(dev);
    assert(RaidWrite(1, buffer, 1) == 0);
    assert(RaidStatus() == RAID_FAILED);
    RaidStop();
    RaidStart(dev);
    RaidStop();
    RaidStart(dev);
    RaidStop();
    RaidStart(dev);
    RaidStop();
    RaidStart(dev);
    RaidStop();
    RaidStart(dev);

    assert(RaidWrite(1, buffer, 1) == 0);
    assert(RaidStatus() == RAID_FAILED);

    RaidStop();
    doneDisks(dev);

    flag = false;
    flag1 = false;

    dev = openDisks();
    RaidCreate(dev);
    RaidStart(dev);

    assert(RaidWrite(0, buffer, 1) == 1);
    assert(RaidWrite(1, buffer, 1) == 1);
    assert(RaidWrite(2, buffer, 1) == 1);

    flag = true;
    assert(RaidWrite(2, buffer, 1) == 1);
    assert(RaidStatus() == RAID_DEGRADED);
    flag = false;
    assert(RaidResync() == 1);
    assert(RaidStatus() == RAID_OK);
    assert(RaidWrite(2, buffer, 1) == 1);

    flag = true;
    assert(RaidWrite(2, buffer, 1) == 1);
    assert(RaidStatus() == RAID_DEGRADED);
    flag = false;
    flag1 = true;
    assert(RaidResync() == 0);
    assert(RaidStatus() == RAID_FAILED);
    assert(RaidWrite(2, buffer, 1) == 0);


    RaidStop();
    doneDisks(dev);
    return 0;
}

#endif /* __PROGTEST__ */
