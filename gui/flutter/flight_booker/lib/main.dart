import 'package:flutter/material.dart';
import 'package:window_manager/window_manager.dart';

const appTitle = 'Book Flight';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await windowManager.ensureInitialized();

  var windowOptions = WindowOptions(size: Size(250, 280), center: true);
  await windowManager.setResizable(false);
  await windowManager.setTitle(appTitle);
  windowManager.waitUntilReadyToShow(windowOptions, () async {
    await windowManager.show();
    await windowManager.focus();
  });

  runApp(const CounterApp());
}

class CounterApp extends StatelessWidget {
  const CounterApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: appTitle,
      theme: ThemeData(colorScheme: ColorScheme.dark()),
      debugShowCheckedModeBanner: false,
      home: const HomeScreen(),
    );
  }
}

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<StatefulWidget> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  var _startDateController = TextEditingController();
  var _returnDateController = TextEditingController();

  FlightType _flightType = FlightType.oneWay;
  DateTime? _startDate;
  DateTime? _returnDate;

  void _onSelectFlightType(FlightType? flightType) {
    setState(() {
      _flightType = flightType ?? FlightType.oneWay;
    });
  }

  void _onChangeStartDate(String value) {
    setState(() {
      _startDate = _parseDate(value);
    });
  }

  void _onChangeReturnDate(String value) {
    setState(() {
      _returnDate = _parseDate(value);
    });
  }

  bool get canBook => switch (_flightType) {
    FlightType.oneWay => _startDate != null,
    FlightType.$return =>
      _startDate != null &&
          _returnDate != null &&
          _returnDate!.isAfter(_startDate!),
  };

  DateTime? _parseDate(String dateStr) {
    var split = dateStr.split(' ');
    if (split.length != 1) return null;

    split = split.first.split('.');
    if (split.length != 3) return null;

    final [year, month, day] = split.map((part) => int.tryParse(part)).toList();
    if (year == null || month == null || day == null) return null;

    final date = DateTime(year, month, day);
    if (_formatDate(date.year, date.month, date.day) !=
        _formatDate(year, month, day)) {
      return null;
    }

    return date;
  }

  String _formatDate(int year, int month, int day) {
    return "$year.${month.toString().padLeft(2, '0')}.${day.toString().padLeft(2, '0')}";
  }

  String _formatDateToDisplay(DateTime date) {
    return "${date.day.toString().padLeft(2, '0')}.${date.month.toString().padLeft(2, '0')}.${date.year}";
  }

  String get _message => switch (_flightType) {
    FlightType.oneWay =>
      'You have booked a one-way flight on ${_formatDateToDisplay(_startDate!)}',
    FlightType.$return =>
      'You have booked a one-way flight on ${_formatDateToDisplay(_startDate!)} to ${_formatDateToDisplay(_returnDate!)}',
  };

  @override
  void initState() {
    final now = DateTime.now();
    final tomorrow = now.add(Duration(days: 1));

    _startDate = DateTime(now.year, now.month, now.day);
    _returnDate = DateTime(tomorrow.year, tomorrow.month, tomorrow.day);

    _startDateController.text = _formatDate(now.year, now.month, now.day);
    _returnDateController.text = _formatDate(
      tomorrow.year,
      tomorrow.month,
      tomorrow.day,
    );

    super.initState();
  }

  @override
  void dispose() {
    _startDateController.dispose();
    _returnDateController.dispose();

    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: Padding(
          padding: const EdgeInsets.all(20),
          child: Column(
            spacing: 12,
            crossAxisAlignment: CrossAxisAlignment.stretch,
            children: [
              DropdownMenu(
                initialSelection: FlightType.oneWay,
                width: double.infinity,
                dropdownMenuEntries: FlightType.entries,
                onSelected: _onSelectFlightType,
              ),
              TextField(
                controller: _startDateController,
                style: TextStyle(color: _startDate == null ? Colors.red : null),
                decoration: InputDecoration(
                  border: OutlineInputBorder(),
                  enabledBorder:
                      _startDate == null
                          ? OutlineInputBorder(
                            borderSide: BorderSide(color: Colors.red),
                          )
                          : null,
                  focusedBorder:
                      _startDate == null
                          ? OutlineInputBorder(
                            borderSide: BorderSide(color: Colors.red, width: 2),
                          )
                          : null,
                ),
                onChanged: _onChangeStartDate,
              ),
              TextField(
                controller: _returnDateController,
                style: TextStyle(
                  color: _returnDate == null ? Colors.red : null,
                ),
                decoration: InputDecoration(
                  border: OutlineInputBorder(),
                  enabledBorder:
                      _returnDate == null
                          ? OutlineInputBorder(
                            borderSide: BorderSide(color: Colors.red),
                          )
                          : null,
                  focusedBorder:
                      _returnDate == null
                          ? OutlineInputBorder(
                            borderSide: BorderSide(color: Colors.red, width: 2),
                          )
                          : null,
                ),
                onChanged: _onChangeReturnDate,
                enabled: _flightType == FlightType.$return,
              ),
              FilledButton(
                style: FilledButton.styleFrom(
                  shape: const RoundedRectangleBorder(
                    borderRadius: BorderRadius.all(Radius.circular(4)),
                  ),
                ),
                onPressed:
                    canBook
                        ? () {
                          showDialog(
                            context: context,
                            builder: (context) {
                              return AlertDialog(
                                insetPadding: EdgeInsets.all(20),
                                content: Text(_message),
                                actions: [
                                  FilledButton(
                                    onPressed: () {
                                      Navigator.of(context).pop();
                                    },
                                    style: FilledButton.styleFrom(
                                      shape: const RoundedRectangleBorder(
                                        borderRadius: BorderRadius.all(
                                          Radius.circular(4),
                                        ),
                                      ),
                                    ),
                                    child: const Text("OK"),
                                  ),
                                ],
                              );
                            },
                          );
                        }
                        : null,
                child: Text("Book"),
              ),
            ],
          ),
        ),
      ),
    );
  }
}

enum FlightType {
  oneWay("one-way"),
  $return("return");

  const FlightType(this.label);
  final String label;

  static final entries =
      values
          .map(
            (flightType) => DropdownMenuEntry(
              value: flightType,
              label: "${flightType.label} flight",
            ),
          )
          .toList();
}
