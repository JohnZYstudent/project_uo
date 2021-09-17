//
//  MainScreen.swift
//  FinalProject
//
//  Created by Ziyuan Zhou on 7/10/20.
//  Copyright © 2020 John Zhou. All rights reserved.
//

import SwiftUI

struct MainScreen: View {
    @ObservedObject var CountryStatsViewModel: CountryStatsViewModel
    var body: some View {
        NavigationView{
            VStack{
                if(CountryStatsViewModel.country == nil || CountryStatsViewModel.states.isEmpty){
                    Text("Loading....")
                }else{
                    NavigationLink(destination: CountryMap(CountryStatsViewModel: CountryStatsViewModel)) {
                        Text ("States Map").font(.title).fontWeight(.bold).foregroundColor(.black)
                    }.buttonStyle(PlainButtonStyle())
                    NavigationLink(destination: StateList(CountryStatsViewModel: CountryStatsViewModel)) {
                        Text ("States List").font(.title).fontWeight(.bold).foregroundColor(.black)
                    }.buttonStyle(PlainButtonStyle())
//                    Text(String(self.CountryStatsViewModel.states[0].death))
                }
            }
            .navigationBarTitle("STATES COVID STATS")
        }.onAppear { self.CountryStatsViewModel.loadRecentCountryStats() }
        .onDisappear { self.CountryStatsViewModel.cancelLoad() }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        let viewModel = CountryStatsViewModel()

        return MainScreen(CountryStatsViewModel: viewModel)
    }
}
