SeLoger.com API:
============

WebService:
===========

Base url: http://ws.seloger.com

Nb total d'annonce: BaseUrl/nbAnnoncesTotal.xml
-------------------

Details annonce: BaseUrl/nnonceDetail.xml?
----------------

Id de l'annonce (idAnnonce): numerique (idAnnonce=66972645)

Audiotel (noAudiotel): numerique 0 ou 1 (noAudiotel=1)

Requete de recherche: BaseUrl/search.xml?
---------------------

Page de recherche (SEARCHpg): numerique (SEARCHpg=2)

Type de recherche (idtt): numerique (idtt=2)
    Location: 1
    Achat: 2

Localisation (ci): 1 ou plusieurs numerique separé par une virgule (ci=330192,330363)

Type de bien (idtypebien): 1 ou plus numerique separé par une virgule (idtypebien=1,2,3,4,6,7,8,9,11,12,13,14,15)
    Appartement: 1
    Maison / Villa: 2
    Parking / Box: 3
    Terrain: 4
    Boutique: 6
    Local Commercial: 7
    Bureaux: 8
    Loft / Atelier / Surface: 9
    Immeuble: 11
    Betiment: 12
    Chateau: 13
    Hotel particulier: 14
    Programme: 15

Nombre de piece (nb_pieces): 1 ou plusieurs numerique/chaine separé par une virgule (nb_pieces=1,2,3,4,+5,all)

Nombre de chambres (nb_chambres): 1 ou plusieurs numerique/chaine separé par une virgule (nb_chambres=1,2,3,4,+5,all)

Budget minimum (pxmin): numerique (pxmin=150000)

Budget maximum (pxmax): numerique (pxmax=200000)

Surface minimum (surfacemin): numerique (surfacemin=80)

Surface maximum (surfacemax): numerique (surfacemax=110)

Surface terrain mminimum (surf_terrainmin): numerique (surf_terrainmin=700)

Surface terrain maximum (surf_terrainmax): numerique (surf_terrainmax=1500)

Tri (tri): chaine (tri=a_dt_crea)
    Date ascendant: a_dt_crea
    Date descendant: d_dt_crea
    Prix ascendant: a_px
    Prix descendant: d_px
    Surface ascendant: a_surface
    Surface descendant: d_surface

Avancé:
    Ascenseur: si_ascenseur=1
    Digicode: si_digicode=1
    Interphone: si_interphone=1
    Gardien: si_gardien=1
    Piscine: si_piscine=1
    Terrasse: si_terrasse=1
    Balcon: nb_balconsmin=1
    Parking: si_parkings=1
    Box: si_boxes=1
    Cave: si_cave=1
