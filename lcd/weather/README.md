The Weather information is spread between three different areas: the top-left short information and two weather related pages.

#### Short info
The short weather information is shown on all pages and gives a quick weather overview. It contains of a weather icon in a bigger font (weather.forecast_home), the current temperature (weather.forecast_home.temperature), the humidity (weather.forecast_home.humidity), and the cloud coverage (weather.forecast_home.cloud_coverage).

![Screenshot](./screenshot1.jpg)

#### Current weather
![Screenshot](./screenshot3.jpg)

#### Weather forecast
![Screenshot](./screenshot2.jpg)

This page uses the LVGL line widget to show the weather forecast. In addition, it uses two template sensors that I have defined in my Home-Assistent sever to query a weather forecast and send the corresponding data as text_sensor. Here is the template definition:
```Yaml
template:
  - trigger:
      - platform: time_pattern
        minutes: "/30"
    action:
      - service: weather.get_forecasts
        data:
          type: daily
        target:
          entity_id: weather.forecast_home
        response_variable: daily
      - variables:
          days: "{{ daily['weather.forecast_home'].forecast }}"
    sensor:
      - name: "Daily forecast"
        unique_id: daily_forecast
        state: >
          {% set weather = {
            "sunny": "\U000F0599",
            "clear-day": "\U000F0599", 
            "clear-night": "\U000F0594", 
            "cloudy": "\U000F0590", 
            "rainy": "\U000F0597", 
            "sleet": "\U000F067F", 
            "snow": "\U000F0598", 
            "wind": "\U000F059D", 
            "fog": "\U000F0591", 
            "partlycloudy": "\U000F0595", 
          } %}
          {% for state in days -%}
            {{ as_timestamp(state.datetime)|timestamp_custom("%a") }};{{state.templow}};{{ state.temperature }};{{ state.precipitation }};{{ weather[state.condition] }}#
          {% endfor %}
  - trigger:
      - platform: time_pattern
        minutes: "/10"
    action:
      - service: weather.get_forecasts
        data:
          type: hourly
        target:
          entity_id: weather.forecast_home
        response_variable: hourly
      - variables:
          hours: "{{ hourly['weather.forecast_home'].forecast }}"
    sensor:
      - name: "Hourly forecast"
        unique_id: hourly_forecast
        state: >
          {% for state in hours -%}
            {{ as_timestamp(state.datetime)|timestamp_custom("%H") }};{{ state.temperature }}#
          {% endfor %}
```

Updating the line graphs is done in a complex !lambda expression that splits all the data from the text sensors and updated LVGL label texts and the line-data using a call to lv_line_set_points().