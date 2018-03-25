//
//  TimerView.swift
//  Pomodoro Enterprise
//
//  Created by Andrey Babushkin on 15/11/2017.
//  Copyright © 2017 Andrey Babushkin. All rights reserved.
//

import UIKit

enum TimerState {
    case Rest
    case Work
}

class TimerView: UIView {
    
    private var timerPosition = 0.0
    private var state: TimerState = .Work
    
    private var stateChanged = true
    
    private weak var backgroundLayer: CAShapeLayer?
    private weak var timeElapsedLayer: CAShapeLayer?

    public func update(withPosition pos: Double, andState state: TimerState) {
        self.timerPosition = pos
        
        if (self.state != state) {
            self.stateChanged = true
            self.state = state
        } else {
            self.stateChanged = false
        }
        
        self.setNeedsDisplay()
    }
    
    override func draw(_ rect: CGRect) {
        
        let width = rect.width > rect.height ? rect.height : rect.width
        
        if let _ = self.backgroundLayer {
            self.backgroundLayer!.removeFromSuperlayer()
            self.backgroundLayer = nil
        }
        
        if let _ = self.timeElapsedLayer {
            self.timeElapsedLayer!.removeFromSuperlayer()
            self.timeElapsedLayer = nil
        }
        
        if (self.backgroundLayer == nil || self.stateChanged) {
            drawBackgroundLayer(withEdgeSize: width)
        }
        
        if (self.timerPosition > 0) {
            drawTimeElapsedLayer(withEdgeSize: width)
        }
    }

    private func drawBackgroundLayer(withEdgeSize width: CGFloat) {
        let fullCircleBezier = UIBezierPath(arcCenter: CGPoint(x: width/2, y: width/2),
                                            radius: (width - 3) / 2,
                                            startAngle: 0,
                                            endAngle: .pi * 2,
                                            clockwise: false)
        
        let backgroundTimerLayer = CAShapeLayer()
        backgroundTimerLayer.path = fullCircleBezier.cgPath
        
        let isRest = (self.state == .Rest)
        
        backgroundTimerLayer.strokeColor = (!isRest) ? Colors.lightPink.cgColor : Colors.lightGreen.cgColor
        backgroundTimerLayer.fillColor = UIColor.clear.cgColor
        backgroundTimerLayer.lineWidth = 5.0
        
        self.backgroundColor = .clear
        self.layer.addSublayer(backgroundTimerLayer)
        self.backgroundLayer = backgroundTimerLayer
    }
    
    private func drawTimeElapsedLayer(withEdgeSize width: CGFloat) {
        
        let position = 3 * Double.pi / 2 + 2 * Double.pi * timerPosition
        
        let timeElapsedBezier = UIBezierPath(arcCenter: CGPoint(x: width/2, y: width/2),
                                             radius: (width - 3) / 2,
                                             startAngle: 3 * .pi / 2,
                                             endAngle: CGFloat(position),
                                             clockwise: true)
        
        let isRest = (self.state == .Rest)
        
        let timeElapsedLayer = CAShapeLayer()
        timeElapsedLayer.path = timeElapsedBezier.cgPath
        timeElapsedLayer.strokeColor = (!isRest) ? Colors.pink.cgColor : Colors.green.cgColor
        timeElapsedLayer.fillColor = UIColor.clear.cgColor
        timeElapsedLayer.lineWidth = 5.0
        
        self.layer.addSublayer(timeElapsedLayer)
        self.timeElapsedLayer = timeElapsedLayer
    }
}
