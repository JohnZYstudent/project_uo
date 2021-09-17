//
//  StateCell.swift
//  FinalProject
//
//  Created by Ziyuan Zhou on 7/10/20.
//  Copyright © 2020 John Zhou. All rights reserved.
//

import SwiftUI

struct StateCell: View {
    @ObservedObject var state: StateStats
    var body: some View {
        HStack {
            Text(state.stateName)
            .font(.body)
            .bold()
            .padding(.bottom, 4)
            
            VStack(alignment: .leading) {
                Text("Test Postive:" + String(state.testPositive))
                    .font(.caption).padding(.top, 4)
                
                Text("Test Negative:" + String(state.testNegative))
                .font(.caption).padding(.top, 4)

            }
        }
    }
}

struct StateCell_Previews: PreviewProvider {
    static var previews: some View {
        let viewModel = CountryStatsViewModel()
        return List (viewModel.states,id: \.stateName){ index in
            return StateCell(state: index)
        }
    }
}
