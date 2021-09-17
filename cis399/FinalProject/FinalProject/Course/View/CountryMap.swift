//
//  CountryMap.swift
//  FinalProject
//
//  Created by Ziyuan Zhou on 7/10/20.
//  Copyright © 2020 John Zhou. All rights reserved.
//

import SwiftUI

struct CountryMap: View {
    @ObservedObject var CountryStatsViewModel: CountryStatsViewModel
    @State var statename: String = ""
    @State private var isEditing = false
    var body: some View {
        ScrollView {
            HStack {
                link(state: statename, states: self.CountryStatsViewModel.states)
                TextField("Search ...", text: $statename)
                .padding(7)
                .padding(.horizontal, 25)
                .background(Color(.systemGray6))
                .cornerRadius(8)
                .padding(.horizontal, 10)
                .onTapGesture {
                    self.isEditing = true
                }
                if isEditing {
                    Button(action: {
                    self.isEditing = false
                    self.statename = ""
                }) {
                    Text("Cancel")
                }
                .padding(.trailing, 10)
                .transition(.move(edge: .trailing))
                .animation(.default)
                }
            }
            
            VStack {
                HStack{
                    Image("CountryMap")
                    .resizable()
                    .aspectRatio(contentMode: .fit)
                    .frame(height: 300)
                }
                HStack {
                    Text("Test Postive: " + String(self.CountryStatsViewModel.country!.testPositive))
                        .font(.title)
                        .fontWeight(.bold)
                        .foregroundColor(Color.black)
                    Text("+" + String(self.CountryStatsViewModel.country!.positiveIncrease))
                        .foregroundColor(Color.red)
                }
                HStack {
                    Text("Death: " + String(self.CountryStatsViewModel.country!.death))
                        .font(.title)
                        .fontWeight(.bold)
                        .foregroundColor(Color.black)
                    Text("+" + String(self.CountryStatsViewModel.country!.deathIncrease))
                        .foregroundColor(Color.red)
                }
                Group {
                    Text("Test Negative: " + String(self.CountryStatsViewModel.country!.testNegative))
                    Text("Recovered: " + String(self.CountryStatsViewModel.country!.recovered))
                    Text("Hospitalized Current: " + String(self.CountryStatsViewModel.country!.hospitalizedCurrent))
                    Text("Hospitalized Cumulative: " + String(self.CountryStatsViewModel.country!.hospitalizedCumulative))
                    Text("ICU Current: " + String(self.CountryStatsViewModel.country!.inIcuCurrent))
                    Text("ICU Cumulative: " + String(self.CountryStatsViewModel.country!.inIcuCumulative))
                }
                
            }
        }
    }
}

private func link(state: String, states: Array<StateStats>) -> some View {
    NavigationLink(destination: StateGeneral(state: find(name: state, states: states))) {
        Text("Go")
    }.buttonStyle(PlainButtonStyle())
}

private func find(name: String, states: Array<StateStats>) -> StateStats {
    for state in states {
        if (state.stateName == name) {
            return state
        }
    }
    return states[0]
}

struct CountryMap_Previews: PreviewProvider {
    static var previews: some View {
        let viewModel = CountryStatsViewModel()

        return CountryMap(CountryStatsViewModel: viewModel)
    }
}
