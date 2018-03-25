//
//  ViewController.swift
//  BI-IOS
//
//  Created by Andrey Babushkin on 23/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit
import MapKit
import CoreLocation
import SnapKit
import MagicalRecord

class CheckinAnnotation: MKPointAnnotation {
    var checkin: Checkin!
}

class MapViewController: UIViewController,
                      NSFetchedResultsControllerDelegate,
                      CLLocationManagerDelegate,
                      MKMapViewDelegate {

    weak var mapView: MKMapView!
    var locationManager: CLLocationManager!
    
    var lastCoords: CLLocationCoordinate2D?
    
    var checkinFRC: NSFetchedResultsController<Checkin>!
    
    override func loadView() {
        super.loadView()
        
        let mapView = MKMapView()
        view.addSubview(mapView)
        mapView.snp.makeConstraints { make in
            make.edges.equalToSuperview()
        }
        
        let checkinButton = UIButton()
        checkinButton.setImage(#imageLiteral(resourceName: "checkin"), for: .normal)
        mapView.addSubview(checkinButton)
        checkinButton.snp.makeConstraints { make in
            make.width.height.equalTo(70)
            make.bottom.equalToSuperview().offset(-30)
            make.right.equalToSuperview().offset(-30)
        }
        checkinButton.addTarget(self, action: #selector(checkinButtonPressed(_:)), for: .touchUpInside)
        self.mapView = mapView
    }
    
    func controllerDidChangeContent(_ controller: NSFetchedResultsController<NSFetchRequestResult>) {
        mapView.removeAnnotations(mapView.annotations)
        
        let checkins = controller.fetchedObjects as! [Checkin]
        
        checkins.forEach { checkin in
            let annotation = CheckinAnnotation()
            annotation.checkin = checkin
            annotation.coordinate = CLLocationCoordinate2D(latitude: checkin.lat,
                                                           longitude: checkin.lon)
            annotation.title = checkin.username
            let df = DateFormatter()
            df.dateFormat = "dd/MM/YYYY hh:mm a"
            annotation.subtitle = df.string(from: checkin.time!)
            mapView.addAnnotation(annotation)
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        locationManager = CLLocationManager()
        locationManager.delegate = self
        locationManager.requestWhenInUseAuthorization()
        
        mapView.delegate = self
        
        checkinFRC = Checkin.mr_fetchAllSorted(by: "time",
                                               ascending: true,
                                               with: nil,
                                               groupBy: nil,
                                               delegate: self) as! NSFetchedResultsController<Checkin>
        
        try! checkinFRC.performFetch()
    }

    let reuseIdentifier = "checkinAnnotationReuseID"
    
    func mapView(_ mapView: MKMapView, viewFor annotation: MKAnnotation) -> MKAnnotationView? {
        
        if annotation is MKUserLocation {
            return nil
        }
        
        if let checkinAnnotation = annotation as? CheckinAnnotation {
            let annotationView = mapView.dequeueReusableAnnotationView(withIdentifier: reuseIdentifier) ?? MKAnnotationView(annotation: annotation, reuseIdentifier: reuseIdentifier)
            
            if let gender = checkinAnnotation.checkin.gender {
                switch gender {
                case "male":
                    annotationView.image = #imageLiteral(resourceName: "male")
                case "female":
                    annotationView.image = #imageLiteral(resourceName: "female")
                default:
                    annotationView.image = #imageLiteral(resourceName: "unknown")
                }
            } else {
                annotationView.image = #imageLiteral(resourceName: "unknown")
            }
            
            annotationView.canShowCallout = true
            
            let button = UIButton(type: .detailDisclosure)
            annotationView.rightCalloutAccessoryView = button
            
            return annotationView
        } else {
            return nil
        }
    }
    
    func locationManager(_ manager: CLLocationManager, didChangeAuthorization status: CLAuthorizationStatus) {
        if status == .authorizedWhenInUse {
            mapView.showsUserLocation = true
            mapView.userTrackingMode = .follow
            
            locationManager.startUpdatingLocation()
        }
    }
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        let loc = locations.last!
        self.lastCoords = loc.coordinate
    }
    
    @objc func checkinButtonPressed(_ sender: UIButton) {
        if let coords = lastCoords {
            let storyboard : UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
            let dest = storyboard.instantiateViewController(withIdentifier: "checkinVC") as! CheckinViewController
            dest.date = Date()
            dest.longitude = coords.longitude
            dest.latitude = coords.latitude
            
            let navigationController = UINavigationController(rootViewController: dest)
            present(navigationController, animated: true, completion: nil)
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
}

