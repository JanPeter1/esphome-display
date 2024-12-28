The printer page uses special template sensors to show the current ink level of our printer (Canon).
Starting point is the [Internet Printing Protocol (IPP)](https://www.home-assistant.io/integrations/ipp) service in HomeAssistant. Since the ink sensors in this service are set to "unknown" when the printer is off (which it is most of the time), I created five template sensors that just keep the last known valid value.
```Yaml
template:
  - sensor:
      - name: "Tintenfüllstand Cyan"
        unique_id: tintenfullstand_cyan
        state: >
          {{ iif(is_state('sensor.canon_ts6300_series_cyan', 'unavailable'), states('sensor.tintenfullstand_cyan'), states('sensor.canon_ts6300_series_cyan')) }}
  - sensor:
      - name: "Tintenfüllstand Magenta"
        unique_id: tintenfullstand_magenta
        state: >
          {{ iif(is_state('sensor.canon_ts6300_series_magenta', 'unavailable'), states('sensor.tintenfullstand_magenta'), states('sensor.canon_ts6300_series_magenta')) }}
  - sensor:
      - name: "Tintenfüllstand Yellow"
        unique_id: tintenfullstand_yellow
        state: >
          {{ iif(is_state('sensor.canon_ts6300_series_yellow', 'unavailable'), states('sensor.tintenfullstand_yellow'), states('sensor.canon_ts6300_series_yellow')) }}
  - sensor:
      - name: "Tintenfüllstand Black(BK)"
        unique_id: tintenfullstand_black_bk
        state: >
          {{ iif(is_state('sensor.canon_ts6300_series_black_bk', 'unavailable'), states('sensor.tintenfullstand_black_bk'), states('sensor.canon_ts6300_series_black_bk')) }}
  - sensor:
      - name: "Tintenfüllstand Black(PGBK)"
        unique_id: tintenfullstand_black_pgbk
        state: >
          {{ iif(is_state('sensor.canon_ts6300_series_black_pgbk', 'unavailable'), states('sensor.tintenfullstand_black_pgbk'), states('sensor.canon_ts6300_series_black_pgbk')) }}
```

With these template sensons, a simple bar chart is created to show the current (last known) ink level.

Additionally, I used the [Input Number](https://www.home-assistant.io/integrations/input_number/) integration to allow the input on how many spare ink tanks we have in stock, so that you can decide, when to buy new ink tanks.
![Screenshot](screenshot1.jpg)