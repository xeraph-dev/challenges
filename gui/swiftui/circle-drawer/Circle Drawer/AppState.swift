import SwiftUI

enum HistoryAction {
    case append(CirclePoint), update(CirclePoint, CirclePoint)
}

class AppState: ObservableObject {
    @Published var selected: CirclePoint?
    @Published var cacheSelected: CirclePoint?
    @Published var circles = [CirclePoint]()
    @Published var history = [HistoryAction]()
    @Published var historyIndex = -1
    var canUndo: Bool { historyIndex >= 0 }
    var canRedo: Bool { historyIndex < history.count - 1 }

    func undo() {
        guard canUndo else { return }
        switch history[historyIndex] {
        case .append: let _ = circles.popLast()
        case let .update(prev, curr):
            guard let index = circles.firstIndex(of: curr) else { break }
            circles[index] = prev.copy() as! CirclePoint
        }

        historyIndex -= 1
    }

    func redo() {
        guard canRedo else { return }
        historyIndex += 1
        switch history[historyIndex] {
        case let .append(circle): circles.append(circle.copy() as! CirclePoint)
        case let .update(prev, curr):
            guard let index = circles.firstIndex(of: prev) else { break }
            circles[index] = curr.copy() as! CirclePoint
        }
    }

    func fixHistory() {
        if historyIndex < history.count - 1 {
            print("\(historyIndex) | \(history.count)")
            history.removeLast(history.count - 1 - historyIndex)
        }
    }

    func append(_ circle: CirclePoint) {
        fixHistory()
        history.append(.append(circle))
        historyIndex += 1
    }

    func update() {
        guard let cacheSelected else { return }
        guard let selected else { return }
        guard selected != cacheSelected else { return }
        fixHistory()
        history.append(.update(
            cacheSelected.copy() as! CirclePoint,
            selected.copy() as! CirclePoint
        ))
        historyIndex += 1
        self.cacheSelected = nil
        self.selected = nil
    }
}
