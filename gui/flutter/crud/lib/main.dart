import 'package:flutter/material.dart';
import 'package:uuid/uuid.dart';
import 'package:window_manager/window_manager.dart';

const appTitle = 'CRUD';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await windowManager.ensureInitialized();

  var windowOptions = WindowOptions(size: Size(600, 400), center: true);
  await windowManager.setResizable(false);
  await windowManager.setTitle(appTitle);
  windowManager.waitUntilReadyToShow(windowOptions, () async {
    await windowManager.show();
    await windowManager.focus();
  });

  runApp(const CRUDApp());
}

class CRUDApp extends StatelessWidget {
  const CRUDApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: appTitle,
      debugShowCheckedModeBanner: false,
      theme: ThemeData(colorScheme: ColorScheme.dark()),
      home: const HomeScreen(),
    );
  }
}

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  final _nameController = TextEditingController();
  final _surnameController = TextEditingController();

  var _filter = "";

  final _users = <User>[];
  int _selected = -1;

  List<User> get _filtered =>
      _users
          .where(
            (user) =>
                user.surname.toLowerCase().startsWith(_filter.toLowerCase()),
          )
          .toList();

  void _onSelectUser(int index) {
    setState(() {
      _selected = index;
    });
    if (index >= 0) {
      final user = _filtered[index];
      _nameController.text = user.name;
      _surnameController.text = user.surname;
    }
  }

  void _onFilter(String value) {
    setState(() {
      _filter = value;
    });
  }

  void _onCreate() {
    setState(() {
      _users.add(
        User(name: _nameController.text, surname: _surnameController.text),
      );
    });
    _reset();
  }

  void _onUpdate() {
    final selected = _filtered[_selected];
    final index = _users.indexWhere((user) => user.id == selected.id);
    setState(() {
      _users[index].name = _nameController.text;
      _users[index].surname = _surnameController.text;
    });

    _reset();
  }

  void _onDelete() {
    final selected = _filtered[_selected];
    final index = _users.indexWhere((user) => user.id == selected.id);
    setState(() {
      _users.removeAt(index);
    });
    _reset();
  }

  void _reset() {
    setState(() {
      _selected = -1;
    });
    _nameController.clear();
    _surnameController.clear();
  }

  @override
  void dispose() {
    _nameController.dispose();
    _surnameController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        padding: EdgeInsets.all(20),
        child: Column(
          spacing: 12,
          children: <Widget>[
            Expanded(
              child: Row(
                spacing: 12,
                children: [
                  Expanded(
                    child: Column(
                      spacing: 12,
                      children: [
                        Row(
                          spacing: 12,
                          children: [
                            Text("Filter prefix:"),
                            Expanded(child: _input(null, _onFilter)),
                          ],
                        ),
                        Expanded(
                          child: Container(
                            decoration: BoxDecoration(
                              border: Border.all(
                                color: ColorScheme.of(context).primary,
                              ),
                              borderRadius: BorderRadius.circular(4),
                            ),
                            child: ListView.builder(
                              itemCount: _filtered.length,
                              itemBuilder:
                                  (context, index) => ListTile(
                                    selectedColor:
                                        ColorScheme.of(context).onPrimary,
                                    selectedTileColor:
                                        ColorScheme.of(context).primary,
                                    selected: index == _selected,
                                    onTap: () => _onSelectUser(index),
                                    title: Text(
                                      "${_filtered[index].surname}, ${_filtered[index].name}",
                                    ),
                                  ),
                            ),
                          ),
                        ),
                      ],
                    ),
                  ),
                  Expanded(
                    child: Column(
                      spacing: 12,
                      children: [
                        SizedBox(height: 48),
                        Row(
                          spacing: 12,
                          children: [
                            SizedBox(width: 64, child: Text("Name:")),
                            Expanded(
                              child: _input(_nameController, (value) {}),
                            ),
                          ],
                        ),
                        Row(
                          spacing: 12,
                          children: [
                            Text("Surname:"),
                            Expanded(
                              child: _input(_surnameController, (value) {}),
                            ),
                          ],
                        ),
                      ],
                    ),
                  ),
                ],
              ),
            ),
            Row(
              spacing: 12,
              children: [
                _button("Create", _onCreate),
                _button("Update", _selected >= 0 ? _onUpdate : null),
                _button("Delete", _selected >= 0 ? _onDelete : null),
              ],
            ),
          ],
        ),
      ),
    );
  }

  TextField _input(
    TextEditingController? controller,
    void Function(String value) onChanged,
  ) => TextField(
    controller: controller,
    decoration: InputDecoration(border: OutlineInputBorder()),
    onChanged: onChanged,
  );

  FilledButton _button(String text, void Function()? onPressed) => FilledButton(
    style: FilledButton.styleFrom(
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(4)),
    ),
    onPressed: onPressed,
    child: Text(text),
  );
}

class User {
  User({required this.name, required this.surname});

  final String id = Uuid().v4();
  String name;
  String surname;
}
