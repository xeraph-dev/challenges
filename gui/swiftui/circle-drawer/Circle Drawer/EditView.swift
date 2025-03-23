import SwiftUI

struct EditView: View {
    @EnvironmentObject var state: AppState
    @State var d: CGFloat = 0

    var body: some View {
        VStack {
            Text(
                "Adjust diameter of circle at (\(String(format: "%.1f", state.selected?.x ?? 0)), \(String(format: "%.1f", state.selected?.y ?? 0)))"
            )
            Slider(value: $d, in: 0 ... 100)
                .frame(width: 200)
        }
        .onAppear {
            guard let selected = state.selected else { return }
            d = selected.d
        }
        .onChange(of: d) {
            guard let selected = state.selected else { return }
            selected.d = $0
            state.selected = selected
        }
        .padding()
    }
}

struct EditView_Previews: PreviewProvider {
    static var previews: some View {
        EditView()
            .environmentObject(AppState())
    }
}
