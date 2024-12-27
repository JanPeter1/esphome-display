![solar page](screenshot1.jpg)

The solar pages shows some information about our PV installation. It uses the [SolarEdge](https://www.home-assistant.io/integrations/solaredge) component from HomeAssistant.

- current power: sensor.solaredge_current_power
- energy today: sensor.solaredge_energie_heute
- grid power: sensor.solaredge_netzstrom either in white or in red
- highest peak time: sensor.power_highest_peak_time_today
- degree of self-sufficiency: solaredge_selbst_verbrauchte_energie * 100 / sensor.solaredge_verbrauchte_energie
- energy this year: solaredge_energie_in_diesem_jahr