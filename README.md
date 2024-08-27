Notice:
- This project has some errors that I haven't fixed, UDS.c should be an example only and need some modification for submitting
- Errors:
  + SID 27 have problem with some test: send seed, send wrong key then although you request seed or send a key(may be matched key), system must start a timer and
  wait for 10sec, delay should be used only if you cant deploy timer properly
  + SID 2E should be rewrite based on mine
- Bosch project consist 2 excercise, this is ex2, CAN Diagnostic
- You shouldn't write all function in main, with 2 excercises , write 2 library for each then call them in main.c and main.h
- Files to read(when you learn about this project)
  + RM0090(search in gg)
  + stm32f4xx_hal_can.h
  + stm32f4xx_hal_can.c
  + stm32f4xx_it.h
  + stm32f4xx_it.c
  + main.h
