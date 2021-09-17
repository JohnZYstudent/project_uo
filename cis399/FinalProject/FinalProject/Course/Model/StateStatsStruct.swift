//
//  StateStatsStruct.swift
//  FinalProject
//
//  Created by Ziyuan Zhou on 7/10/20.
//  Copyright © 2020 John Zhou. All rights reserved.
//

import Foundation

struct StateStatsStruct {
    let stateName: String
    let testPostive: Int
    let postiveIncrease: Int
    let testNegative: Int
    let negativeIncrease: Int
    let hospitalizedCurrent: Int
    let hospitalizedCumulative: Int
    let hospitalizedIncrease: Int
    let inIcuCurrently: Int
    let inIcuCumulative: Int
    let onVentilatorCurrently: Int
    let onVentilatorCumulative: Int
    let death: Int
    let deathIncrease: Int
    let recovered: Int
    var isWatched: Bool = false
    
//    let date ?
    
}
