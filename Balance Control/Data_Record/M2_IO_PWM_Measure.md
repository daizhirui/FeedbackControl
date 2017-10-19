# M2 IO PWM Measure Data

**Motor Driver is set at 800 Hz**
| PWM HALF T | Unload_Frequency(Hz) | Load_Frequency(Hz) | Motor State |
|:----------:|:---------:|:---:|:--:|
|5|8876.71||
|10|6147.75|8876.71|
|11|||
|15|4702.54|6148.72|
|16||5792.56|
|17|||
|18||5190.80|
|19|||
|20|3807.24||
|25|3198.63||
|30|2758.31||
|35|2423.67||
|40|2161.44||
|45|1950.09||
|50|1777.88||
|55|1632.09||
|60|1508.80||
|65|1403.13||
|70|1312.13||
|75|1230.92||
|80|1159.49||
|85|1095.89||
|90|1038.16||
|95|987.279||
|100|940.313||
|200|497.064||
|300|331.702||
|400|249.510||
|500|199.608||
|600|166.340||
|700|142.857||
|800|125.244||
|900|111.546||
|1000|99.8043||
|1100|90.0195||
|1200|83.1702||
|1300|77.2994||

## Conclusion
The unloading-frequency and loading-frequency are different. So the best way to control the speed is to measure it with the help of the motor encoder and adjust the pwm_half_T according to the statistics.