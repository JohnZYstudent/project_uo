//
//  StateStats+CoreDataProperties.swift
//  FinalProject
//
//  Created by Ziyuan Zhou on 7/14/20.
//  Copyright © 2020 John Zhou. All rights reserved.
//

import Foundation
import CoreData


extension StateStats {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<StateStats> {
        return NSFetchRequest<StateStats>(entityName: "StateStats")
    }

    @NSManaged public var stateName: String
    @NSManaged public var testPositive: Int
    @NSManaged public var testNegative: Int
    @NSManaged public var negativeIncrease: Int
    @NSManaged public var positiveIncrease: Int
    @NSManaged public var hospitalizedCumulative: Int
    @NSManaged public var hospitalizedCurrent: Int
    @NSManaged public var hospitalizedIncrease: Int
    @NSManaged public var inIcuCumulative: Int
    @NSManaged public var inIcuCurrent: Int
    @NSManaged public var onVentilatorCumulative: Int
    @NSManaged public var onVentilatorCurrent: Int
    @NSManaged public var recovered: Int
    @NSManaged public var death: Int
    @NSManaged public var deathIncrease: Int
    @NSManaged public var isWatched: Bool
    
    @NSManaged public var country: CountryStats
}
