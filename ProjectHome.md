# System wymiany komunikatów #

Projekt zaliczeniowy realizowany na Wydziale Elektroniki i Technik Informacyjnych, Politechniki Warszawskiej.

## Cel ##
Zaprojektować i zaimplementować system wymiany informacji o użytkownikach oraz wysyłanie wiadomości tekstowych pomiędzy użytkownikami. System powinien umożliwiać wykonanie następujących operacji przez użytkowników:

  * Podłączanie / odłączenie się od systemu,
  * Sprawdzenie stanu innego użytkownika (dostępny / niedostępny),
  * Wysłanie komunikatu tekstowego do podłączonego użytkownika,
  * Wysłanie pliku do podłączonego użytkownika.

System powinien być obsługiwany przez kilka serwerów. Użytkownik może podłączyć się do dowolnego z nich.

Pliki przesyłane pomiędzy użytkownikami mają być przesyłane bez udziału serwerów w przekazywaniu danych. W przypadku braku możliwości bezpośredniego połączenia pomiędzy użytkownikami dane mają być przesyłane za pośrednictwem innego użytkownika.

Implementacje systemu (serwery oraz aplikacje klienckie) należy wykonać na różnych platformach (Windows, Linux; Java, C++, C# - kod zarządzany).

## Autorzy ##
Marian Szczykulski,
Mateusz Kołodziejczyk,
Wojciech Grześkowiak
