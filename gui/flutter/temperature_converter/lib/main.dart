import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:window_manager/window_manager.dart';

const appTitle = 'Temperature Converter';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await windowManager.ensureInitialized();

  var windowOptions = WindowOptions(size: Size(400, 120), center: true);
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
  final _celsiusController = TextEditingController(text: '0');
  final _fahrenheitController = TextEditingController(text: "32");

  void _onChangeCelsius(String value) {
    final celsius = double.tryParse(value) ?? 0;
    _fahrenheitController.text = (celsius * (9 / 5) + 32).toStringAsFixed(1);
  }

  void _onChangeFahrenheit(String value) {
    final fahrenheit = double.tryParse(value) ?? 0;
    _celsiusController.text = ((fahrenheit - 32) * (5 / 9)).toStringAsFixed(1);
  }

  @override
  void dispose() {
    _celsiusController.dispose();
    _fahrenheitController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: Padding(
          padding: const EdgeInsets.all(20),
          child: Row(
            spacing: 12,
            children: [
              Expanded(
                child: TextField(
                  controller: _celsiusController,
                  keyboardType: TextInputType.numberWithOptions(decimal: true),
                  inputFormatters: [NumberInputFormatter()],
                  decoration: InputDecoration(border: OutlineInputBorder()),
                  onChanged: _onChangeCelsius,
                ),
              ),
              Text("Celsius"),
              Text('='),
              Expanded(
                child: TextField(
                  controller: _fahrenheitController,
                  keyboardType: TextInputType.numberWithOptions(decimal: true),
                  inputFormatters: [NumberInputFormatter()],
                  decoration: InputDecoration(border: OutlineInputBorder()),
                  onChanged: _onChangeFahrenheit,
                ),
              ),
              Text("Fahrenheit"),
            ],
          ),
        ),
      ),
    );
  }
}

class NumberInputFormatter extends TextInputFormatter {
  @override
  TextEditingValue formatEditUpdate(
    TextEditingValue oldValue,
    TextEditingValue newValue,
  ) =>
      RegExp(r'^-?\d*(\d\.)?\d*$').hasMatch(newValue.text)
          ? newValue
          : oldValue;
}
