//
//  StatisticsViewController.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 21/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import CoreData
import CorePlot

class StatisticsViewController: UIViewController, NSFetchedResultsControllerDelegate, CPTPlotDataSource, CPTAxisDelegate {

    @IBOutlet weak var avatarButton: UIButton!
    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var pomodorosCounterLabel: UILabel!
    @IBOutlet weak var tasksCounterLabel: UILabel!
    @IBOutlet weak var plotView: CPTGraphHostingView!
    
    var personFRC: NSFetchedResultsController<PersonCD>!
    var pomodoroFRC: NSFetchedResultsController<PomodoroCD>!
    var taskFRC: NSFetchedResultsController<TaskCD>!
    var settingsFRC: NSFetchedResultsController<SettingsCD>!
    
    var completedTasksWeek: [Int32] = [10, 11, 12, 13, 15, 18, 19]
    var completedPomosWeek: [Int32] = [19, 12, 15, 12, 11, 19, 10]
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let pred = NSPredicate(format: "main = true")
        personFRC = PersonCD.mr_fetchAllSorted(by: "name",
                                               ascending: true,
                                               with: pred,
                                               groupBy: nil,
                                               delegate: self) as! NSFetchedResultsController<PersonCD>
        
        pomodoroFRC = PomodoroCD.mr_fetchAllSorted(by: "pdate",
                                                   ascending: false,
                                                   with: nil,
                                                   groupBy: nil,
                                                   delegate: self) as! NSFetchedResultsController<PomodoroCD>
        
        taskFRC = TaskCD.mr_fetchAllSorted(by: "dateFinish",
                                           ascending: false,
                                           with: nil,
                                           groupBy: nil,
                                           delegate: self) as! NSFetchedResultsController<TaskCD>
        
        settingsFRC = SettingsCD.mr_fetchAllSorted(by: "personUsersUserId",
                                                   ascending: true,
                                                   with: nil,
                                                   groupBy: nil,
                                                   delegate: self) as! NSFetchedResultsController<SettingsCD>
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        updateViewPerson()
        updateViewSettings()
        updateViewPomodoro()
        updateViewTask()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        setupGraphView()
        updateViewPerson()
    }
    
    func controllerDidChangeContent(_ controller: NSFetchedResultsController<NSFetchRequestResult>) {
        switch controller {
        case personFRC:
            updateViewPerson()
        case pomodoroFRC:
            updateViewPomodoro()
        case taskFRC:
            updateViewTask()
        case settingsFRC:
            updateViewSettings()
        default:
            break
        }
        setupGraphView()
    }
    
    func updateViewPerson() {
        try! personFRC.performFetch()
        let per = personFRC.fetchedObjects
        
        if let ps = per, ps.count > 0 {
            let p = ps[0]
            nameLabel.text = p.name! + " " + p.familyName!
            
            if let a = p.avatar {
                let img = ImageUtilities.base64ToImage(base64str: a)
                avatarButton.setImage(img, for: .normal)
            }
        }
    }
    
    func updateViewPomodoro() {
        let p = pomodoroFRC.fetchedObjects
        completedPomosWeek = [0, 0, 0, 0, 0, 0, 0]
        
        if let ps = p {
            ps.filter { $0.pdate != nil }
              .forEach { pomo in
                let secInOneDay = 86400.0
                
                for i in 0..<7 {
                    let date = NSDate(timeIntervalSinceNow: Double(-i) * secInOneDay)
                    let pomoDate = pomo.pdate!
                    
                    if (datesEqual(date1: date as Date, date2: pomoDate)) {
                        completedPomosWeek[i] += 1
                    }
                }
            }
        }
        
        let f = { (l: UILabel, c: Int32) in
            let old = l.text?.split(separator: "/")
            let nums = old?.map { str in return str.trimmingCharacters(in: [" "])}
            let goal = Int(nums![1])
            l.text = "\(c) / \(goal!)"
        }
        
        f(pomodorosCounterLabel, completedPomosWeek[0])
    }
    
    func updateViewTask() {
        let t = taskFRC.fetchedObjects
        completedTasksWeek = [0, 0, 0, 0, 0, 0, 0]
        
        if let ts = t {
            ts.filter { $0.dateFinish != nil }
              .forEach { task in
                let secInOneDay = 86400.0
                
                for i in 0..<7 {
                    let date = NSDate(timeIntervalSinceNow: Double(-i) * secInOneDay)
                    let taskDate = task.dateFinish!
                    
                    if (datesEqual(date1: date as Date, date2: taskDate)) {
                        completedTasksWeek[i] += 1
                    }
                }
            }
            
            let f = { (l: UILabel, c: Int32) in
                let old = l.text?.split(separator: "/")
                let nums = old?.map { str in return str.trimmingCharacters(in: [" "])}
                let goal = Int(nums![1])
                l.text = "\(c) / \(goal!)"
            }
            
            f(tasksCounterLabel, completedTasksWeek[0])
        }
    }
    
    func updateViewSettings() {
        let s = settingsFRC.fetchedObjects
        
        if let ss = s, ss.count > 0 {
            let set = ss[0]
            
            let f = { (l: UILabel, g: Int32) in
                let old = l.text?.split(separator: "/")
                let nums = old?.map { str in return str.trimmingCharacters(in: [" "])}
                let compl = Int(nums![0])
                l.text = "\(compl!) / \(g)"
            }
            
            let taskGoal = set.taskGoal
            let pomGoal = set.pomodoroGoal
            f(tasksCounterLabel, taskGoal)
            f(pomodorosCounterLabel, pomGoal)
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func datesEqual(date1: Date, date2: Date) -> Bool {
        let currCalendar = NSCalendar.current
        
        let date1Comps = currCalendar.dateComponents([.year,.month,.day], from: date1)
        let date2Comps = currCalendar.dateComponents([.year,.month,.day], from: date2)
        
        let date1WoTime = currCalendar.date(from: date1Comps)
        let date2WoTime = currCalendar.date(from: date2Comps)
        
        let dateCompResult = date1WoTime!.compare(date2WoTime!)
        
        switch dateCompResult {
        case .orderedSame:
            return true
        default:
            return false
        }
    }
    
    // MARK: - Plot methods
    
    func setupGraphView() {
        let graph = CPTXYGraph(frame: plotView.frame)
        plotView.hostedGraph = graph
        guard let plotSpace = graph.defaultPlotSpace as? CPTXYPlotSpace else { return }
        plotSpace.xRange = CPTPlotRange(locationDecimal: CPTDecimalFromDouble(-1),
                                        lengthDecimal: CPTDecimalFromDouble(8))
        let yMin = [completedPomosWeek.min()!, completedTasksWeek.min()!].min()!
        let yMax = [completedPomosWeek.max()!, completedTasksWeek.max()!].max()!
        plotSpace.yRange = CPTPlotRange(locationDecimal: CPTDecimalFromDouble(Double(yMin) - 8.0),
                                        lengthDecimal: CPTDecimalFromDouble(Double(yMax - yMin) + 10.0))
        
        //graph.apply(CPTTheme(named: CPTThemeName.plainWhiteTheme))
        graph.fill = CPTFill(color: CPTColor.clear())
        graph.paddingBottom = 0.0
        graph.paddingLeft = 0.0
        graph.paddingTop = 0.0
        graph.paddingRight = 0.0
        graph.plotAreaFrame?.borderLineStyle = nil
        
        let axisSet = graph.axisSet as! CPTXYAxisSet
        if let x = axisSet.xAxis {
            x.labelRotation = .pi / 2
            x.labelingPolicy = .none
            var customTickLocations: [NSDecimalNumber] = []
            var customLabels: [String] = []
            for i in 0..<7 {
                customTickLocations.append(NSDecimalNumber(value: i))
                customLabels.append(dateForIndex(i))
            }
            
            var labelLocation = 0
            var customAxisLabels: [CPTAxisLabel] = []
            
            for tickLoc in customTickLocations {
                let label = CPTAxisLabel(text: (customLabels[labelLocation]), textStyle: x.labelTextStyle)
                labelLocation += 1
                label.tickLocation = tickLoc.decimalNumber()
                label.offset = x.labelOffset + x.majorTickLength
                label.rotation = .pi / 2
                customAxisLabels.append(label)
            }
            
            x.axisLabels = Set(customAxisLabels)

            x.majorIntervalLength   = 1
            x.orthogonalPosition    = yMin - 1 as NSNumber
            x.minorTicksPerInterval = 1
            
            x.visibleRange = CPTPlotRange(locationDecimal: CPTDecimalFromDouble(-1),
                                          lengthDecimal: CPTDecimalFromDouble(8))
        }
        
        if let y = axisSet.yAxis {
            
            var customTickLocations: [NSDecimalNumber] = []
            var customLabels: [Int32] = []
            for i in yMin...yMax {
                customTickLocations.append(NSDecimalNumber(value: i))
                customLabels.append(i)
            }
            
            var labelLocation = 0
            var customAxisLabels: [CPTAxisLabel] = []
            
            for tickLoc in customTickLocations {
                let label = CPTAxisLabel(text: "\(customLabels[labelLocation])", textStyle: y.labelTextStyle)
                labelLocation += 1
                label.tickLocation = tickLoc.decimalNumber()
                label.offset = 12 *  y.labelOffset
                customAxisLabels.append(label)
            }
            
            y.axisLabels = Set(customAxisLabels)
            
            y.majorIntervalLength   = 1
            y.minorTicksPerInterval = 0
            y.orthogonalPosition    = -0.5
            y.delegate = self
            
            y.visibleRange = CPTPlotRange(locationDecimal: CPTDecimalFromDouble(Double(yMin)),
                                          lengthDecimal: CPTDecimalFromDouble(Double(yMax - yMin)) + 2)
        }
        
        let taskPlot = CPTScatterPlot(frame: graph.frame)
        taskPlot.dataSource = self
        taskPlot.delegate = self
        taskPlot.identifier = NSString(string: "TaskPlot")
        
        let blueLineStyle = CPTMutableLineStyle()
        blueLineStyle.miterLimit    = 1.0
        blueLineStyle.lineWidth     = 3.0
        blueLineStyle.lineColor     = CPTColor.blue()
        taskPlot.dataLineStyle = blueLineStyle
        
        let taskSymbolLineStyle = CPTMutableLineStyle()
        taskSymbolLineStyle.lineColor = .blue()
        let blueSymbol = CPTPlotSymbol.ellipse()
        blueSymbol.fill          = CPTFill(color: .blue())
        blueSymbol.lineStyle     = taskSymbolLineStyle
        blueSymbol.size          = CGSize(width: 10.0, height: 10.0)
        taskPlot.plotSymbol = blueSymbol
        
        let pomoPlot = CPTScatterPlot(frame: graph.frame)
        pomoPlot.dataSource = self
        pomoPlot.delegate = self
        pomoPlot.identifier = NSString(string: "PomoPlot")
        
        let redLineStyle = CPTMutableLineStyle()
        redLineStyle.miterLimit    = 1.0
        redLineStyle.lineWidth     = 3.0
        redLineStyle.lineColor     = CPTColor.red()
        pomoPlot.dataLineStyle = redLineStyle
        
        let pomoSymbolLineStyle = CPTMutableLineStyle()
        pomoSymbolLineStyle.lineColor = .red()
        let redSymbol = CPTPlotSymbol.ellipse()
        redSymbol.fill          = CPTFill(color: .red())
        redSymbol.lineStyle     = pomoSymbolLineStyle
        redSymbol.size          = CGSize(width: 10.0, height: 10.0)
        pomoPlot.plotSymbol = redSymbol
        
        graph.add(taskPlot, to: graph.defaultPlotSpace)
        graph.add(pomoPlot, to: graph.defaultPlotSpace)
    }
    
    func numberOfRecords(for plot: CPTPlot) -> UInt {
        let id = plot.identifier as! NSString
        switch id {
        case NSString(string: "TaskPlot"):
            return UInt(completedTasksWeek.count)
        case NSString(string: "PomoPlot"):
            return UInt(completedPomosWeek.count)
        default:
            return 0
        }
    }
    
    func number(for plot: CPTPlot, field fieldEnum: UInt, record idx: UInt) -> Any? {
        let id = plot.identifier as! NSString
        switch fieldEnum {
        case UInt(CPTScatterPlotField.X.rawValue):
            return idx
        case UInt(CPTScatterPlotField.Y.rawValue):
            switch id {
            case NSString(string: "TaskPlot"):
                return completedTasksWeek[Int(6 - idx)]
            case NSString(string: "PomoPlot"):
                return completedPomosWeek[Int(6 - idx)]
            default:
                return 0
            }
        default:
            return 0
        }
        
        
    }
    
    func axis(_ axis: CPTAxis, shouldUpdateAxisLabelsAtLocations locations: Set<NSNumber>) -> Bool {
        return false
    }
    
    func dateForIndex(_ idx: Int) -> String {
        let secInOneDay = 86400.0
        let form = DateFormatter()
        form.dateFormat = "dd/MM/yyyy"
        let today = NSDate(timeIntervalSinceNow: Double(-(6 - idx)) * secInOneDay)
        return form.string(from: today as Date)
    }

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
