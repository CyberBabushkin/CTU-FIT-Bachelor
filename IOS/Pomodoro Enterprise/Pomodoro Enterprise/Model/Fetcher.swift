import CoreData
import Sync
import Alamofire

extension Dictionary {
    var json: String {
        let invalidJson = "Not a valid JSON"
        do {
            let jsonData = try JSONSerialization.data(withJSONObject: self, options: .prettyPrinted)
            return String(bytes: jsonData, encoding: String.Encoding.utf8) ?? invalidJson
        } catch {
            return invalidJson
        }
    }
    func dict2json() -> String {
        return json
    }
}

extension Collection where Iterator.Element == [String:Any] {
    func toJSONString(options: JSONSerialization.WritingOptions = .prettyPrinted) -> String {
        if let arr = self as? [[String:Any]],
            let dat = try? JSONSerialization.data(withJSONObject: arr, options: options),
            let str = String(data: dat, encoding: String.Encoding.utf8) {
            return str
        }
        return "[]"
    }
}

class Fetcher {
    private let dataStack: DataStack
    
    init() {
        self.dataStack = DataStack(modelName: "Pomodoro_Enterprise")
    }
    
    func fetchLocals<T: NSManagedObject>() -> [T] {
        let request: NSFetchRequest<T> = T.fetchRequest() as! NSFetchRequest<T>
        
        return try! self.dataStack.viewContext.fetch(request)
    }
    
    func allLocalsToJSON<T: NSManagedObject>(class _: T.Type) -> String {
        let request: NSFetchRequest<T> = T.fetchRequest() as! NSFetchRequest<T>
        let list = try! self.dataStack.viewContext.fetch(request)
        var jsons: [[String : Any]] = []
        for nso in list {
            jsons.append(nso.export())
        }
        
        return jsons.toJSONString()
    }
    
    func localToJson<T: NSManagedObject>(object: T) -> String {
        let obj = object.export()
        return obj.dict2json()
    }
}

enum VoidResult {
    case success
    case failure(NSError)
}

