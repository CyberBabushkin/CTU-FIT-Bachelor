//
//  CheckinViewController.swift
//  BI-IOS
//
//  Created by Andrey Babushkin on 23/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import MapKit

class MapViewWithZoom: MKMapView {
    
    var zoomLevel: Double {
        get {
            return Double(log2(360 * (Double(self.frame.size.width/256) / self.region.span.longitudeDelta)) + 1);
        }
        
        set (newZoomLevel){
            setCenterCoordinate(coordinate: self.centerCoordinate, zoomLevel: newZoomLevel, animated: false)
        }
    }
    
    private func setCenterCoordinate(coordinate: CLLocationCoordinate2D, zoomLevel: Double, animated: Bool){
        let span = MKCoordinateSpanMake(0, 360 / pow(2, zoomLevel) * Double(self.frame.size.width) / 256)
        setRegion(MKCoordinateRegionMake(centerCoordinate, span), animated: animated)
    }
}

class CheckinViewController: UIViewController {
    
    @IBOutlet weak var nameTextField: UITextField!
    @IBOutlet weak var genderSelector: UISegmentedControl!
    @IBOutlet weak var mapView: MapViewWithZoom!
    @IBOutlet weak var honestyTextArea: UITextView!
    
    var date: Date!
    var longitude: Double!
    var latitude: Double!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let coords = CLLocationCoordinate2D(latitude: latitude, longitude: longitude)
        mapView.zoomLevel = 15
        mapView.setCenter(coords, animated: false)
        let annotation = MKPointAnnotation()
        annotation.coordinate = CLLocationCoordinate2D(latitude: latitude,
                                                       longitude: longitude)
        mapView.addAnnotation(annotation)
        
        mapView.isZoomEnabled = false
        mapView.isScrollEnabled = false
        mapView.isUserInteractionEnabled = false
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    
    @IBAction func infoPressed(_ sender: Any) {
        honestyTextArea.isHidden = !honestyTextArea.isHidden
    }
    
    @IBAction func savePressed(_ sender: Any) {
        let username = nameTextField.text?.trimmingCharacters(in: [" "])
        var user: String? = nil
        if let u = username, !u.isEmpty {
            user = username
        }
        
        var gender: Gender? = nil
        
        switch genderSelector.selectedSegmentIndex {
        case 0:
            gender = .Female
        case 1:
            gender = .Male
        default:
            break
        }
        
        DatabaseSync.shared.createCheckin(withDate: date, lattitude: latitude, longitude: longitude, username: user, gender: gender)
        
        dismiss(animated: true, completion: nil)
    }
    
    @IBAction func cancelPressed(_ sender: Any) {
        dismiss(animated: true, completion: nil)
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
