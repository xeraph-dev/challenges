import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter/physics.dart';
import 'package:window_manager/window_manager.dart';

const appTitle = 'Timer';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await windowManager.ensureInitialized();

  var windowOptions = WindowOptions(size: Size(300, 210), center: true);
  await windowManager.setResizable(false);
  await windowManager.setTitle(appTitle);
  windowManager.waitUntilReadyToShow(windowOptions, () async {
    await windowManager.show();
    await windowManager.focus();
  });

  runApp(const TimerApp());
}

class TimerApp extends StatelessWidget {
  const TimerApp({super.key});

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
  late Timer _timer;

  var _elapsed = 0.0;
  var _duration = 5.0;

  double get progress => _elapsed / _duration;

  @override
  void initState() {
    _startTimer();
    super.initState();
  }

  void _onChangeDuration(double value) {
    setState(() {
      _duration = value;
    });
    if (!_timer.isActive) _startTimer();
  }

  void _onReset() {
    _timer.cancel();
    setState(() {
      _elapsed = 0;
    });
    _startTimer();
  }

  void _startTimer() {
    _timer = Timer.periodic(Duration(milliseconds: 100), (timer) {
      if (_elapsed > _duration || nearEqual(_elapsed, _duration, 0.0001)) {
        timer.cancel();
        return;
      }
      setState(() {
        _elapsed += 0.1;
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        padding: EdgeInsets.all(20),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            Row(
              spacing: 8,
              children: [
                Text("Elapsed Time:"),
                Expanded(
                  child: LinearProgressIndicator(
                    minHeight: 20,
                    borderRadius: BorderRadius.circular(4),
                    value: progress,
                  ),
                ),
              ],
            ),
            SizedBox(height: 16),
            Row(
              spacing: 8,
              children: [Text("${_elapsed.toStringAsFixed(1)}s")],
            ),
            Row(
              spacing: 8,
              children: [
                Text("Duration:"),
                Expanded(
                  child: Slider(
                    value: _duration,
                    min: 0,
                    max: 20,
                    onChanged: _onChangeDuration,
                  ),
                ),
              ],
            ),
            SizedBox(height: 4),
            FilledButton(
              style: FilledButton.styleFrom(
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(4),
                ),
              ),
              onPressed: _onReset,
              child: Text("Reset"),
            ),
          ],
        ),
      ),
    );
  }
}
