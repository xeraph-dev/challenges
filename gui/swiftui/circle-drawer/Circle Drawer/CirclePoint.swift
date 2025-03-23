import Foundation

class CirclePoint: Equatable, Identifiable, NSCopying {
    func copy(with _: NSZone? = nil) -> Any {
        let copy = CirclePoint(id: id, x: x, y: y)
        copy.d = d
        return copy
    }

    static func == (lhs: CirclePoint, rhs: CirclePoint) -> Bool {
        (lhs.id, lhs.x, lhs.y, lhs.d) == (rhs.id, rhs.x, rhs.y, rhs.d)
    }

    let id: Int
    let x: CGFloat
    let y: CGFloat
    var d: CGFloat = 20

    init(id: Int, x: CGFloat, y: CGFloat) {
        self.id = id
        self.x = x
        self.y = y
    }

    static func `default`() -> CirclePoint {
        CirclePoint(id: 0, x: 0, y: 0)
    }
}
