//
//  StateList.swift
//  FinalProject
//
//  Created by Ziyuan Zhou on 7/10/20.
//  Copyright © 2020 John Zhou. All rights reserved.
//

import SwiftUI

struct StateList: View {
    @ObservedObject var CountryStatsViewModel: CountryStatsViewModel
    var body: some View {
            List {
                    Section {
                        Toggle("Show Watched State", isOn:self.$CountryStatsViewModel.showWatchedOnly)
                    }

                    Section {
                        ForEach(CountryStatsViewModel.states, id: \.stateName) { state in
                            Section() {
                                link(state: state)
                            }
                        }
                    }
                }.listStyle(GroupedListStyle()).navigationBarTitle("States List")
    }
}
private func link(state: StateStats) -> some View {
       NavigationLink(destination: StateDetail(state: state)) {
           StateCell(state: state)
       }
   }
struct StateList_Previews: PreviewProvider {
    static var previews: some View {
        let viewModel = CountryStatsViewModel()

        return StateList(CountryStatsViewModel: viewModel)
    }
}
