![Screenshot](./screenshot1.jpg)

There's nothing special in this folder. It uses simple lambda expressions to convert the current date into German abbreviations. A time_update script is called every 60 seconds to update the three time labels.

```Yaml
script:
  - id: time_update
    then:
      - lvgl.label.update:
          id: label_time1
          text: !lambda |-
            static char time_buf[15];
            auto now = id(time_comp).now();
            snprintf(time_buf, sizeof(time_buf), "%02d:%02d", now.hour, now.minute);
            return time_buf;
      - lvgl.label.update:
          id: label_time2
          text: !lambda |-
            static const char * const day_names[] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
            auto now = id(time_comp).now();
            return day_names[now.day_of_week - 1];
      - lvgl.label.update:
          id: label_time3
          text: !lambda |-
            static const char * const mon_names[] = {"JAN", "FEB", "MÄR", "APR", "MAI", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DEZ"};
            static char date_buf[15];
            auto now = id(time_comp).now();
            snprintf(date_buf, sizeof(date_buf), "%2d. %s %4d", now.day_of_month, mon_names[now.month-1], now.year);
            return date_buf;
```