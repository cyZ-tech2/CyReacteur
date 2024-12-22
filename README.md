# CyWATT ⚡

Pre-Ing 2 <br>
Sujet : [C-Wire](Projet_C-Wire.pdf) <br>
Rapport : [Rapport](RapportProjet.pdf) <br>

## Projet

Bievenue sur CyWatt !


Notre programme a pour objectif d’analyser des types de stations (HV-B, HV-A ou LV) afin de déterminer si elles sont en situation de surproduction ou de sous-production d’énergie. Par ailleurs, il nous permettra donc de savoir quelle proportion de leur énergie est consommé par les entreprises et les particuliers

## Arguments 

- fichier_entrée 
- type_station : (hvb, hva ou lv)
- type_consommateur : (comp, indiv ou all)
- centrale_id : l'ID de la centrale électrique (Optionnel)

Cas indisponibles : hvb indiv/all et hva indiv/all

### Commande

```bash
bash ./c-wire.sh input/[fichier_entrée] [type_station(hvb, hva, lv)] [type_consommateur(indiv, comp, all)] (centrale_id)
```

### Exemple

```bash
bash ./c-wire.sh input/c-wire_v25.dat hva comp
```

## Contributeur

Ziyad HADDADI MI05 <br>
Florian BRYUANT MI04 <br>
