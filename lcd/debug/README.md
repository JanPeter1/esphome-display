This page usually is not included - it just shows a bit of debugging information, most notably the free memory. It used the debug sensor and some "lambda magic" to split the texts into smaller parts.

```Yaml
debug:
  update_interval: 60s

text_sensor:
  - platform: debug
    device:
      name: "Device Info"
      on_value:
        # '2024.12.2|Chip: ESP32-S3 Features:WIFI_BGN,BLE, Cores:2 Revision:2|ESP-IDF: 5.1.5|EFuse MAC: F0:F5:BD:4B:95:B0|Reset: Software Reset Digital Core|Wakeup: Unknown'
        then: !
          lambda: |-
            std::string txt(x);
            int pos;
            // ESPHome version
            lv_label_set_text(debug_text1t, "ESPHome");
            pos = txt.find('|');
            lv_label_set_text(debug_text1, txt.substr(0, pos).c_str());
            txt = txt.substr(pos+1);
            ...
```