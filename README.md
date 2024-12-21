# CyWATT

Bievenue sur CyWatt !


Notre programme a pour objectif d’analyser des types de stations (HV-B, HV-A ou LV) afin de déterminer si elles sont en situation de surproduction ou de sous-production d’énergie. Par ailleurs, il nous permettra donc de savoir quelle proportion de leur énergie est consommé par les entreprises et les particuliers

## Arguments 

1 - fichier_entrée 
2 - type_station : (hvb, hva ou lv)
3 - type_consommateur : (comp, indiv ou all)
4 - centrale_id : l'ID de la centrale électrique (Optionnel)

Cas indisponibles : hvb indiv/all et hva indiv/all

### Commande

```bash
./c-wire.sh input/[input_file] [type_station(hvb, hva, lv)] [type_consommateur(indiv, comp, all)] (centrale_id)
```

### Exemple

```bash
./c-wire.sh input/c-wire_v25.dat hva comp
```

## Code d'erreur

### Shell erreur

A remplir

### C erreur

A remplir
