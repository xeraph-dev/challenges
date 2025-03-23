import Foundation

struct Todo: Identifiable, Equatable {
    let id = UUID()
    var text: String
    var completed = false
}
