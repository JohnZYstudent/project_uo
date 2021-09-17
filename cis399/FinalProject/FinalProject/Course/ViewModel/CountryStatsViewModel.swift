//
//  StateStatsViewModel.swift
//  FinalProject
//
//  Created by Ziyuan Zhou on 7/10/20.
//  Copyright © 2020 John Zhou. All rights reserved.
//
import Combine
import CoreData
import Foundation

class CountryStatsViewModel: NSObject,ObservableObject,NSFetchedResultsControllerDelegate {
    var country: CountryStats? { return CountryStatsResultsController?.fetchedObjects?.first}
    var states: Array<StateStats> { return StateStatsResultsController?.fetchedObjects ?? []}
    
    private var CountryStatsResultsController: NSFetchedResultsController<CountryStats>?
    private var StateStatsResultsController: NSFetchedResultsController<StateStats>?
    private var loadSubscription: AnyCancellable?
    
    func loadRecentCountryStats() {
        loadSubscription = CountryService.shared.loadRecentCountryStat()
            .sink(receiveCompletion: { result in
                print("Publisher finished with result: \(result)")
            }, receiveValue: {
                // Ignore
            })
    }
    
    func cancelLoad() {
        loadSubscription?.cancel()
        loadSubscription = nil
    }
    
    private func setupStateStatsResults() {
        if let country = self.country {
            StateStatsResultsController = CountryService.shared.recentStateStats(isWatched: showWatchedOnly, countryStats: country, with: self)
        }else{
            StateStatsResultsController = nil
        }
    }
    
    var showWatchedOnly: Bool = false {
        willSet {
            objectWillChange.send()
            
            setupStateStatsResults()
        }
    }

    override init() {
        super.init()
        
        CountryStatsResultsController = CountryService.shared.recentCountryStats(with: self)
        setupStateStatsResults()
    }
    
    func controllerWillChangeContent(_ controller: NSFetchedResultsController<NSFetchRequestResult>) {
        objectWillChange.send()
    }
    
    func controllerDidChangeContent(_ controller: NSFetchedResultsController<NSFetchRequestResult>) {
        if controller == CountryStatsResultsController {
            objectWillChange.send()
            setupStateStatsResults()
        }
    }
}
