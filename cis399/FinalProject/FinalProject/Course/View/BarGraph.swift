//
//  BarGraph.swift
//  FinalProject
//
//  Created by Ziyuan Zhou on 7/10/20.
//  Copyright © 2020 John Zhou. All rights reserved.
//

import SwiftUI

struct BarGraph: View {
    var color: Color
    var scale: CGFloat

    var body: some View {
        GeometryReader{ geometry in
            Rectangle()
                .frame(width: self.scale*geometry.size.width*0.9, height: 50, alignment: .trailing)
                .foregroundColor(self.color).brightness(0.25)
        }.frame(height: 50)
    }
}

struct SwiftUIView_Previews: PreviewProvider {
    static var color: Color = .purple
    static var scale: CGFloat = 208392/208392
    static var previews: some View {
        return BarGraph(color: color,scale: scale)
    }
}
