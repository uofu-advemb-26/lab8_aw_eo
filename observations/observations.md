# LAB 8 ACTIVITY 2



## Before adding busy wait delay

### Predictions

We think that the lower priority message will still be sent in a regular interval. We do not think that the higher priority message will cause significant delay for the lower priority message. 

### Setup

We have set the high priority board (ID 0x100) to `TX_DELAY_MS=0`, so it transmits as soon as each frame is queued. The low priority board (ID 0x200) was set to `TX_DELAY_MS=20`.

### Observations

With these settings we do not see the low priority message at all. The receiver on the high priority board never prints an `rx id=0x200` line.

This is CAN arbitration working as intended. Whenever both boards start transmitting at the same time, the lower ID (0x100) wins, and the low priority board backs off and retries. Because the high priority board always has another frame ready, the bus is never idle long enough for the 0x200 frame to win, so the low priority node is starved.

![No Low Priority Message Oscilloscope][no_low_priority_messsage.pdf]

## After adding busy wait delay


**Assumption:** In order to "introduce a short busy wait delay into the babbling node", we just changed the parameter for which CMAKE assigns to the vTaskDelay line.

### Setup

Our first step was to increase the delay in the higher priority sender to 1ms instead of 0.