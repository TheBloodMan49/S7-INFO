# Recherches dans Splunk

- Les ports liés au Web dans la capture sont 80 et 443.

- On va s'intéresser au port 80 car c'est le port standard de HTTP (non sécurisé)

- Il y a 2 requêtes qui obtiennent un code de retour 200. Elles paraissent suspectes :

  - URI de requête /?status=install et /?status=start&av=Windows Defender
  - User Agent PowerShell 
  - IP source : 10.7.10.47 (local)
  - Destination : 623start.site

- 1 requête obtient un code 301 (Moved permanently)

  - URI /data/czx.jpg
  - Même IP source
  - Pas de User Agent
  - Destination : guiatelefonos.com
  - Redirigé vers HTTPS (port 443)

- Après avoir listé les connexions, une requete sortante de 500ko semble anormale (la dernière sur le screen)

  - Transfert sur un port non standard
  - Inhabituel pour un client d'envoyer autant de données
  - Destination : 194.26.135.119 (Vers l'extérieur)
  
