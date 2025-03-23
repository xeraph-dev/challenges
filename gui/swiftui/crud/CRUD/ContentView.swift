import SwiftUI

class User: Identifiable, Equatable, Hashable {
    static func == (lhs: User, rhs: User) -> Bool {
        (lhs.id, lhs.name, lhs.surname) == (rhs.id, rhs.name, rhs.surname)
    }

    let id: UUID
    var name: String
    var surname: String

    init(_ name: String, _ surname: String) {
        id = UUID()
        self.name = name
        self.surname = surname
    }

    private init(_ id: UUID, _ name: String, _ surname: String) {
        self.id = id
        self.name = name
        self.surname = surname
    }

    func hash(into hasher: inout Hasher) {
        hasher.combine(id)
        hasher.combine(name)
        hasher.combine(surname)
    }

    static func from(_ user: User) -> User {
        User(user.id, user.name, user.surname)
    }
}

struct ContentView: View {
    @State private var filter = ""
    @State private var selected: User?
    @State private var name = ""
    @State private var surname = ""
    @State private var users = [User]()
    @State private var filtered = [User]()
    @State private var error = ""

    var body: some View {
        VStack(alignment: .leading) {
            Grid {
                GridRow {
                    HStack {
                        Text("Filter prefix")
                        TextField("prefix", text: $filter)
                            .cornerRadius(5)
                    }
                    Text(error)
                        .foregroundColor(.red)
                }
                GridRow(alignment: .top) {
                    List(filtered, id: \.self, selection: $selected) { user in
                        Text("\(user.name), \(user.surname)")
                            .onTapGesture(count: 2) { _ in selected = nil }
                            .onTapGesture(count: 1) { _ in selected = user }
                    }
                    .cornerRadius(5)

                    Grid(alignment: .leading) {
                        GridRow {
                            Text("Name:")
                            TextField("name", text: $name)
                                .cornerRadius(5)
                        }

                        GridRow {
                            Text("Surname:")
                            TextField("surname", text: $surname)
                                .cornerRadius(5)
                        }
                    }
                }
            }
            HStack {
                Button("Create") {
                    guard !name.isEmpty && !surname.isEmpty else { return }
                    guard validate() else { return }
                    users.append(User(name, surname))
                    name = ""
                    surname = ""
                }
                Button("Update") {
                    guard let selected else { return }
                    guard let index = users.firstIndex(of: selected) else { return }
                    guard validate() else { return }
                    let user = User.from(selected)
                    user.name = name
                    user.surname = surname
                    users[index] = user
                    self.selected = nil
                }
                .disabled(selected == nil)
                Button("Delete") {
                    guard let selected else { return }
                    guard let index = users.firstIndex(of: selected) else { return }
                    users.remove(at: index)
                    self.selected = nil
                }
                .disabled(selected == nil)
            }
        }
        .onChange(of: name) { _ in
            if !error.isEmpty {
                error = ""
            }
        }
        .onChange(of: surname) { _ in
            if !error.isEmpty {
                error = ""
            }
        }
        .onChange(of: selected) {
            name = $0?.name ?? ""
            surname = $0?.surname ?? ""
        }
        .onChange(of: filter) { _ in
            filtered = filter.isEmpty ? users : users.filter { $0.surname.starts(with: filter) }
        }
        .onChange(of: users) {
            filtered = filter.isEmpty ? $0 : $0.filter { $0.surname.starts(with: filter) }
        }
        .frame(width: 380, height: 200)
        .padding()
    }

    private func validate() -> Bool {
        let exists = users.contains(where: { $0.name == name && $0.surname == surname })
        if exists {
            error = "User already exists"
        }
        return !exists
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
