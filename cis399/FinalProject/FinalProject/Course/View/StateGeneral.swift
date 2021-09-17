//
//  StateGeneral.swift
//  FinalProject
//
//  Created by Ziyuan Zhou on 7/12/20.
//  Copyright © 2020 John Zhou. All rights reserved.
//

import SwiftUI

struct StateGeneral: View {
    
    @ObservedObject var state: StateStats
    
    var body: some View {
        
        VStack {
            Text(state.stateName)
                .font(.largeTitle)
                .fontWeight(.bold)
                .foregroundColor(Color.black)
                .multilineTextAlignment(.center)
 
            Text("Infected Rate: " + String(format:"%.2f",(Float(state.testPositive)/Float(state.testNegative+state.testPositive)*100)) + "%")
                .font(.title)
                .fontWeight(.bold)
                .foregroundColor(Color.black)
                .multilineTextAlignment(.center)
            Text("Postive Increase: " + String(format:"%.2f",(Float(state.positiveIncrease)/Float(state.testPositive)*100)) + "%")
                .font(.title)
                .fontWeight(.bold)
                .foregroundColor(Color.black)
                .multilineTextAlignment(.center)
            Text("Death Rate: " + String(format:"%.2f",(Float(state.death)/Float(state.testPositive)*100)) + "%")
                .font(.title)
                .fontWeight(.bold)
                .foregroundColor(Color.black)
                .multilineTextAlignment(.center)
            Text("Hosptialized increase: " + String(format:"%.2f",(Float(state.hospitalizedIncrease)/Float(state.hospitalizedCurrent)*100)) + "%")
                .font(.title)
                .fontWeight(.bold)
                .foregroundColor(Color.black)
                .multilineTextAlignment(.center)
        }
    }
}

//struct State_Previews: PreviewProvider {
//    @State static var previewState = testData[0]
//    static var previews: some View {
//        StateGeneral(state: $previewState)
//    }
//}

