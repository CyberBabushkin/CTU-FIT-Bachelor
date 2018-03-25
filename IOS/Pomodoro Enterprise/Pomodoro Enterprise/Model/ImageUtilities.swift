//
//  ImageUtilities.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 09/12/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import Foundation
import UIKit

class ImageUtilities: NSObject {
    
    class func resizeImage(image: UIImage, targetSize: CGSize) -> UIImage {
        let size = image.size
        
        let widthRatio  = targetSize.width  / size.width
        let heightRatio = targetSize.height / size.height
        
        // Figure out what our orientation is, and use that to form the rectangle
        var newSize: CGSize
        if(widthRatio > heightRatio) {
            newSize = CGSize(width: size.width * heightRatio, height: size.height * heightRatio)
        } else {
            newSize = CGSize(width: size.width * widthRatio,  height: size.height * widthRatio)
        }
        
        // This is the rect that we've calculated out and this is what is actually used below
        let rect = CGRect(x: 0, y: 0, width: newSize.width, height: newSize.height)
        
        // Actually do the resizing to the rect using the ImageContext stuff
        UIGraphicsBeginImageContextWithOptions(newSize, false, 1.0)
        image.draw(in: rect)
        let newImage = UIGraphicsGetImageFromCurrentImageContext()
        UIGraphicsEndImageContext()
        
        return newImage!
    }
    
    class func imageToBase64(image: UIImage) -> String {
        let imageData = UIImagePNGRepresentation(image)! as NSData
        let strBase64 = imageData.base64EncodedString(options: .endLineWithCarriageReturn)
        return strBase64
    }
    
    class func base64ToImage(base64str: String) -> UIImage {
        let dataDecoded : Data = Data(base64Encoded: base64str, options: .ignoreUnknownCharacters)!
        let decodedimage = UIImage(data: dataDecoded)
        return decodedimage!
    }
}
