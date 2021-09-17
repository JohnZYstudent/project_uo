//
//  StateStatsService.swift
//  FinalProject
//
//  Created by Ziyuan Zhou on 7/13/20.
//  Copyright © 2020 John Zhou. All rights reserved.
//

import Combine
import CoreData
import CoreGraphics

class CountryService {

    private init() {
        persistentContainer = NSPersistentContainer(name: "Model")

        persistentContainer.loadPersistentStores { storeDescription, error in
            if let error = error {
                fatalError("Error loading persistent store \(error as NSError)")
            }

            self.persistentContainer.viewContext.mergePolicy = NSMergeByPropertyObjectTrumpMergePolicy
            self.persistentContainer.viewContext.automaticallyMergesChangesFromParent = true
        }
    }

    private let persistentContainer: NSPersistentContainer

    var viewContext: NSManagedObjectContext { persistentContainer.viewContext }

    static let shared = CountryService()
    
    func recentCountryStats(with delegate: NSFetchedResultsControllerDelegate) -> NSFetchedResultsController<CountryStats>?{
        let fetchRequest: NSFetchRequest<CountryStats> = CountryStats.fetchRequest()
        fetchRequest.sortDescriptors = [NSSortDescriptor(keyPath: \CountryStats.date, ascending: true)]
        let resultsController = NSFetchedResultsController(fetchRequest: fetchRequest, managedObjectContext: persistentContainer.viewContext, sectionNameKeyPath: nil, cacheName: nil)
        resultsController.delegate = delegate
        
        guard let _ = try? resultsController.performFetch() else {
            print("Error performing fetch for recent state Stats")
            
            return nil
        }
        
        return resultsController
    }
    func recentStateStats(isWatched: Bool = false, countryStats: CountryStats,with delegate: NSFetchedResultsControllerDelegate) -> NSFetchedResultsController<StateStats>? {
        let fetchRequest: NSFetchRequest<StateStats> = StateStats.fetchRequest()
        fetchRequest.predicate = NSPredicate(format: "isWatched == %@ AND country == %@", isWatched as NSNumber,countryStats)
        fetchRequest.sortDescriptors = [NSSortDescriptor(keyPath: \StateStats.stateName, ascending: true)]
        let resultsController = NSFetchedResultsController(fetchRequest: fetchRequest, managedObjectContext: persistentContainer.viewContext, sectionNameKeyPath: nil, cacheName: nil)
        resultsController.delegate = delegate

        guard let _ = try? resultsController.performFetch() else {
            print("Error performing fetch for recent state Stats")

            return nil
        }

        return resultsController
    }
    
    
    func loadRecentCountryStat() -> AnyPublisher<Void, Error>{
        var components = URLComponents()
        components.scheme = "https"
        components.host = "covidtracking.com"
        components.path = "/api/v1/us/current.json"
        
        let url = components.url!
        let urlSession = URLSession.shared
        let publisher = urlSession.dataTaskPublisher(for: url)
            .map {(data, _) -> Data in
                
//                let jsonString = String(data: data, encoding: .utf8)
//                print(jsonString)
                
                return data
            }
            .decode(type: Array<CountryStatsDataTransferObject>.self, decoder: jsonDecoder)
            .flatMap { value -> AnyPublisher<Void, Error> in
                return self.loadRecentStateStats(dataTransferObjects: value.first!)
            }
            .receive(on: RunLoop.main)
            .eraseToAnyPublisher()
        
        return publisher
    }
    
    private func loadRecentStateStats(dataTransferObjects: CountryStatsDataTransferObject) -> AnyPublisher<Void, Error>{
        var components = URLComponents()
        components.scheme = "https"
        components.host = "covidtracking.com"
        components.path = "/api/v1/states/current.json"

        let url = components.url!
        let urlSession = URLSession.shared
        let publisher = urlSession.dataTaskPublisher(for: url)
            .map {(data, _) -> Data in
//                     let jsonString = String(data: data, encoding: .utf8)
//                                                print(jsonString)
                return data}
            .decode(type: Array<StateStatsDataTransferObject>.self, decoder: jsonDecoder)
            .flatMap { value -> Empty<Void, Error> in

                self.process(countryDataTransferObjects: dataTransferObjects, stateDataTransferObjects: value)

                return Empty<Void, Error>(completeImmediately: true)
            }
            .eraseToAnyPublisher()

        return publisher
    }
    
    private func process(countryDataTransferObjects: CountryStatsDataTransferObject, stateDataTransferObjects: Array<StateStatsDataTransferObject>) {
        let context = persistentContainer.newBackgroundContext()
        context.mergePolicy = NSMergeByPropertyObjectTrumpMergePolicy
        context.performAndWait {
            do {

                
                let countryStats: CountryStats
                if let existingCountryStats = try fetchCountryStats(withdate: countryDataTransferObjects.date, in: context) {
                    existingCountryStats.update(with: countryDataTransferObjects)
                    
                    countryStats = existingCountryStats
                }
                else {
                    countryStats = CountryStats(context: context, dataTransferObject: countryDataTransferObjects)
                }
                
                for stateDataTransferObject in stateDataTransferObjects {
                    if let existingStateStats = try fetchStateStats(withStateName: stateDataTransferObject.stateName, in: context) {
                        existingStateStats.update(with: stateDataTransferObject)
                    }
                    else {
                        let stateStats = StateStats(context: context, dataTransferObject: stateDataTransferObject)
                        stateStats.country = countryStats
                    }
                }

                try context.save()
            }
            catch let error {
                print("Error saving context: \(error)")
                context.rollback()
            }
        }
    }
    
    private func fetchCountryStats(withdate date: Int,in context: NSManagedObjectContext) throws -> CountryStats? {
       
            let fetchRequest: NSFetchRequest<CountryStats> = CountryStats.fetchRequest()

            fetchRequest.predicate = NSPredicate(format: "date == %@", date as NSNumber)
            fetchRequest.fetchLimit = 1

            return try context.fetch(fetchRequest).first
        }

    private func fetchStateStats(withStateName stateName: String, in context: NSManagedObjectContext) throws -> StateStats? {

        let fetchRequest: NSFetchRequest<StateStats> = StateStats.fetchRequest()

        fetchRequest.predicate = NSPredicate(format: "stateName == %@", stateName)
        fetchRequest.fetchLimit = 1

        return try context.fetch(fetchRequest).first
    }
    private let jsonDecoder = JSONDecoder()
}

fileprivate struct CountryStatsDataTransferObject: Decodable {
    let date: Int
    let testPositive: Int
    let testNegative: Int
    let positiveIncrease: Int
    let hospitalizedCumulative: Int
    let hospitalizedCurrent: Int
    let inIcuCumulative: Int
    let inIcuCurrent: Int
    let onVentilatorCumulative: Int
    let onVentilatorCurrent: Int
    let recovered: Int
    let death: Int
    let deathIncrease: Int
    
    private enum CodingKeys: String, CodingKey {
        case date = "date"
        case testPositive = "positive"
        case testNegative = "negative"
        case positiveIncrease = "positiveIncrease"
        case hospitalizedCumulative = "hospitalizedCumulative"
        case hospitalizedCurrent = "hospitalizedCurrently"
        case inIcuCumulative = "inIcuCumulative"
        case inIcuCurrent = "inIcuCurrently"
        case onVentilatorCumulative = "onVentilatorCumulative"
        case onVentilatorCurrent = "onVentilatorCurrently"
        case recovered = "recovered"
        case death = "death"
        case deathIncrease = "deathIncrease"
    }
}

fileprivate extension CountryStats{
    convenience init(context: NSManagedObjectContext, dataTransferObject: CountryStatsDataTransferObject) {
        self.init(context: context)

        update(with: dataTransferObject)
    }

    func update(with dataTransferObject: CountryStatsDataTransferObject) {
        date = dataTransferObject.date
        testPositive = dataTransferObject.testPositive
        testNegative = dataTransferObject.testNegative
        positiveIncrease = dataTransferObject.positiveIncrease
        hospitalizedCumulative = dataTransferObject.hospitalizedCumulative
        hospitalizedCurrent = dataTransferObject.hospitalizedCurrent
        inIcuCumulative = dataTransferObject.inIcuCumulative
        inIcuCurrent = dataTransferObject.inIcuCurrent
        onVentilatorCumulative = dataTransferObject.onVentilatorCumulative
        onVentilatorCurrent = dataTransferObject.onVentilatorCurrent
        recovered = dataTransferObject.recovered
        death = dataTransferObject.death
        deathIncrease = dataTransferObject.deathIncrease
    }
}
    
fileprivate struct StateStatsDataTransferObject: Decodable {
    let stateName: String
    let testPostive: Int?
    let testNegative: Int?
    let negativeIncrease: Int?
    let postiveIncrease: Int?
    let hospitalizedCumulative: Int?
    let hospitalizedCurrent: Int?
    let hospitalizedIncrease: Int?
    let inIcuCumulative: Int?
    let inIcuCurrent: Int?
    let onVentilatorCumulative: Int?
    let onVentilatorCurrent: Int?
    let recovered: Int?
    let death: Int?
    let deathIncrease: Int?

    private enum CodingKeys: String, CodingKey {
        case stateName = "state"
        case testPostive = "positive"
        case testNegative = "negative"
        case negativeIncrease = "negativeIncrease"
        case postiveIncrease = "positiveIncrease"
        case hospitalizedCumulative = "hospitalizedCumulative"
        case hospitalizedCurrent = "hospitalizedCurrently"
        case hospitalizedIncrease = "hospitalizedIncrease"
        case inIcuCumulative = "inIcuCumulative"
        case inIcuCurrent = "inIcuCurrently"
        case onVentilatorCumulative = "onVentilatorCumulative"
        case onVentilatorCurrent = "onVentilatorCurrently"
        case recovered = "recovered"
        case death = "death"
        case deathIncrease = "deathIncrease"
    }
}

fileprivate extension StateStats{
    convenience init(context: NSManagedObjectContext, dataTransferObject: StateStatsDataTransferObject) {
        self.init(context: context)

        update(with: dataTransferObject)
    }

    func update(with dataTransferObject: StateStatsDataTransferObject) {
        stateName = dataTransferObject.stateName
        testPositive = dataTransferObject.testPostive ?? 0
        testNegative = dataTransferObject.testNegative ?? 0
        negativeIncrease = dataTransferObject.negativeIncrease ?? 0
        positiveIncrease = dataTransferObject.postiveIncrease ?? 0
        hospitalizedCumulative = dataTransferObject.hospitalizedCumulative ?? 0
        hospitalizedCurrent = dataTransferObject.hospitalizedCurrent ?? 0
        hospitalizedIncrease = dataTransferObject.hospitalizedIncrease ?? 0
        inIcuCumulative = dataTransferObject.inIcuCumulative ?? 0
        inIcuCurrent = dataTransferObject.inIcuCurrent ?? 0
        onVentilatorCumulative = dataTransferObject.onVentilatorCumulative ?? 0
        onVentilatorCurrent = dataTransferObject.onVentilatorCurrent ?? 0
        recovered = dataTransferObject.recovered ?? 0
        death = dataTransferObject.death ?? 0
        deathIncrease = dataTransferObject.deathIncrease ?? 0
    }
}
