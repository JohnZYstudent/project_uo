//
//  StateDetail.swift
//  FinalProject
//
//  Created by Ziyuan Zhou on 7/10/20.
//  Copyright © 2020 John Zhou. All rights reserved.
//

import SwiftUI

struct StateDetail: View {
    @ObservedObject var state: StateStats
    
    var body: some View {
        
        ScrollView() {
                VStack(alignment: .leading) {
                    Group{
                        Text("Test")
                        .font(.title)
                        .fontWeight(.bold)
                        .foregroundColor(Color.black)
                        if(state.testPositive + state.testNegative != 0){
                            BarGraph(color: .red, scale: CGFloat(state.testPositive)/CGFloat(state.testPositive + state.testNegative))

                        }else{
                            BarGraph(color: .red, scale: CGFloat(0)/CGFloat(1))
                        }
                        Text("Test Postive: " + String(state.testPositive))
                        .font(.caption)
                        .padding(.leading, 8)
                        .padding(.bottom, 32)
                        if(state.testPositive + state.testNegative != 0){
                            BarGraph(color: .green, scale: CGFloat(state.testNegative)/CGFloat(state.testPositive + state.testNegative))
                        }else{
                            BarGraph(color: .green, scale: CGFloat(0)/CGFloat(1))
                        }
                        Text("Test Negative: " + String(state.testNegative))
                        .font(.caption)
                        .padding(.leading, 8)
                        .padding(.bottom, 32)
                    }
                    
                    Group{
                        Text ("Hospitalized")
                        .font(.title)
                        .fontWeight(.bold)
                        .foregroundColor(Color.black)
                        if(state.hospitalizedCurrent + state.hospitalizedCumulative != 0){
                            BarGraph(color: .red, scale: CGFloat(state.hospitalizedCurrent)/CGFloat(state.hospitalizedCurrent + state.hospitalizedCumulative))
                        }else{
                            BarGraph(color: .red, scale: CGFloat(0)/CGFloat(1))
                        }
                        Text("Hospitalized Current: " + String(state.hospitalizedCurrent))
                        .font(.caption)
                        .padding(.leading, 8)
                        .padding(.bottom, 32)
                        if(state.hospitalizedCurrent + state.hospitalizedCumulative != 0){
                            BarGraph(color: .purple, scale: CGFloat(state.hospitalizedCumulative)/CGFloat(state.hospitalizedCurrent + state.hospitalizedCumulative))
                        }else{
                            BarGraph(color: .purple, scale: CGFloat(0)/CGFloat(1))
                        }
                        Text("Hospitalized Cumulative: " + String(state.hospitalizedCumulative))
                        .font(.caption)
                        .padding(.leading, 8)
                        .padding(.bottom, 32)
                    }

                    Group{
                        Text ("ICU")
                        .font(.title)
                        .fontWeight(.bold)
                        .foregroundColor(Color.black)
                        if(state.inIcuCurrent + state.inIcuCumulative != 0){
                            BarGraph(color: .red, scale: CGFloat(state.inIcuCurrent)/CGFloat(state.inIcuCurrent + state.inIcuCumulative))
                        }else{
                            BarGraph(color: .red, scale: CGFloat(0)/CGFloat(1))
                        }
                        Text("In ICU Current: " + String(state.inIcuCurrent))
                        .font(.caption)
                        .padding(.leading, 8)
                        .padding(.bottom, 32)
                        if(state.inIcuCurrent + state.inIcuCumulative != 0){
                            BarGraph(color: .purple, scale: CGFloat(state.inIcuCumulative)/CGFloat(state.inIcuCurrent + state.inIcuCumulative))
                        }else{
                            BarGraph(color: .purple, scale: CGFloat(0)/CGFloat(1))

                        }
                        Text("In ICU Cumulative: " + String(state.inIcuCumulative))
                        .font(.caption)
                        .padding(.leading, 8)
                        .padding(.bottom, 32)
                    }

                    Group{
                        Text ("Ventilator")
                        .font(.title)
                        .fontWeight(.bold)
                        .foregroundColor(Color.black)
                        if(state.onVentilatorCurrent + state.onVentilatorCumulative != 0){
                            BarGraph(color: .red, scale: CGFloat(state.onVentilatorCurrent)/CGFloat(state.onVentilatorCurrent + state.onVentilatorCumulative))
                        }else{
                            BarGraph(color: .red, scale: CGFloat(0)/CGFloat(1))
                        }
                        Text("On Ventilator Current: " + String(state.onVentilatorCurrent))
                        .font(.caption)
                        .padding(.leading, 8)
                        .padding(.bottom, 32)
                        if(state.onVentilatorCurrent + state.onVentilatorCumulative != 0){
                            BarGraph(color: .purple, scale: CGFloat(state.onVentilatorCumulative)/CGFloat(state.onVentilatorCurrent + state.onVentilatorCumulative))
                        }else{
                            BarGraph(color: .purple, scale: CGFloat(0)/CGFloat(1))
                        }
                        Text("On Ventilator Cumulative: " + String(state.hospitalizedCumulative))
                        .font(.caption)
                        .padding(.leading, 8)
                        .padding(.bottom, 32)
                    }

                    Group{
                        Text ("Patient")
                        .font(.title)
                        .fontWeight(.bold)
                        .foregroundColor(Color.black)
                        if(state.recovered + state.death != 0){
                            BarGraph(color: .red, scale: CGFloat(state.recovered)/CGFloat(state.recovered + state.death))
                        }else{
                            BarGraph(color: .red, scale: CGFloat(0)/CGFloat(1))
                        }
                        Text("Recovered: " + String(state.recovered))
                        .font(.caption)
                        .padding(.leading, 8)
                        .padding(.bottom, 32)
                        if(state.recovered + state.death != 0){
                            BarGraph(color: .purple, scale: CGFloat(state.death)/CGFloat(state.recovered + state.death))
                        }else{
                            BarGraph(color: .purple, scale: CGFloat(0)/CGFloat(1))
                        }
                        Text("Death: " + String(state.death))
                        .font(.caption)
                        .padding(.leading, 8)
                        .padding(.bottom, 32)
                    }
                }
        }.navigationBarTitle(Text(state.stateName)
            .font(.largeTitle)
            .fontWeight(.bold)
                .foregroundColor(Color.black)).navigationBarItems(trailing: Button(action: {
                    self.state.isWatched.toggle()
                }, label: {
                    Image(systemName: state.isWatched ? "eye.slash" : "eye")
                }))
    }
}

//struct StateDetail_Previews: PreviewProvider {
//    static var previews: some View {
//        let context = CountryService.shared.viewContext
//        let
//        StateDetail(state: $previewState)
//    }
//}
