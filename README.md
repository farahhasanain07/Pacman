Jocul Farah's Pacman este o aplicație dezvoltată în limbajul C, care aduce varianta clasică a
legendarului joc de arcade într-un format grafic modern și complet personalizat. Am ales să folosesc
biblioteca Raylib pentru că oferă funcții matematice și de randare hardware-accelerată avansate,
permițându-mi să creez o interfață vizuală superioară și un gameplay fluid. Scopul meu a fost să dezvolt
o experiență de joc stabilă, care nu doar că rulează optim la 60 FPS, dar propune și o identitate estetică
unică.

Logica jocului:
Pentru a asigura o tranziție riguroasă între ecranele de rulare și meniurile interactive, am organizat
arhitectura software pe baza unui automat de stări simplificat (o „mașină cu stări”). O variabilă centrală
stochează starea curentă a aplicației, iar controlul fluxului este gestionat printr-o structură de tip switch.
Aceasta garantează izolarea completă a stărilor: în timpul rulării active, de exemplu, butoanele din
meniuri sunt dezactivate, iar la declanșarea ecranului de Game Over, logica de mișcare a personajelor
este suspendată. Esențială în prevenirea suprapunerii funcțiilor, această arhitectură elimină riscul
apariției bug-urilor de navigare.


Funcțiile principale:

IsValidPacmanMove (și GhostCanMove): Reprezintă rutinele de validare a mișcării. Înainte ca o
entitate să avanseze, funcția analizează coordonatele viitoare în matricea labirintului. Dacă celula
țintă are valoarea 1 (perete), funcția blochează avansul pentru a preveni erorile de tip clipping sau
trecerea prin texturi, iar dacă drumul este liber, permite mișcarea personajului.

UpdateGhostAI: Controlează inteligența artificială a celor 4 fantome. Când o entitate inamică ajunge
la o intersecție, funcția folosește algoritmul geometric Vector2Distance pentru a calcula distanța în
linie dreaptă dintre nodurile libere și poziția curentă a lui Pac-Man, alegendo pe cea care minimizează
această distanță pentru a genera un comportament de urmărire eficient.

DrawHeart: Este funcția responsabilă pentru randarea procedurală a elementelor consumabile. În loc
să încarce imagini externe, aceasta generează geometric o inimă combinând două cercuri adiacente
pentru lobii superiori și un triunghi izoscel inversat pentru vârful inferior, oferind un feedback vizual
clar pentru progresul utilizatorului.
Gestionarea ciclului de desenare: Logica grafică este sincronizată în bucla principală utilizând
cuplul de funcții BeginDrawing() și EndDrawing(). Corelat cu apelul SetTargetFPS(60), acest mecanism asigură împrospătarea constantă a cadrelor, reduce consumul de resurse și elimină complet efectul de flickering grafic.


Compilare și Utilizare:

Proiectul este structurat modular, eliminând dependențele globale prin păstrarea fișierelor bibliotecii
direct în directorul curent.

Ce ai nevoie?

Asigură-te că fișierele raylib.h (header-ul) și libraylib.a (biblioteca statică compilată pentru
Linux) se află în folderul rădăcină al proiectului, alături de fișierele sursă.

Cum pornești jocul?
Compilarea și link-area se efectuează direct din terminal utilizând utilitarul GCC. Tot ce trebuie să faci
este să deschizi terminalul în folderul proiectului și să execuți comanda:
gcc main.c map.c -o farahs_pacman -I. -L. -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

Această instrucțiune se ocupă singură de compilarea modulelor sursă, include directoarele locale (.) și
leagă bibliotecile grafice ale sistemului pentru a genera binarul executabil. Rularea se face prin
comanda:
./farahs_pacman

Structura folderelor:
main.c: Nucleul aplicației, bucla principală și gestionarea input-ului de la tastatură.
map.c și map.h: Modulul care stochează și administrează matricea labirintului.
ghosts.h: Fișierul care conține structurile și algoritmii de AI pentru inamici.
config.h: Fișierul central de configurare ce conține macrodefinițiile și constantele aplicate.
raylib.h și libraylib.a: Dependențele locale ale bibliotecii grafice folosite de aplicație.


Design:
Pentru a implementa bune practici în ingineria software și a păstra codul curat, am izolat structura hărții
într-un modul separat (map.c), definind labirintul printr-o matrice statică de 31x28 elemente întregi. Acest
lucru face aplicația extrem de rapidă: programul modifică dinamic doar valorile din matrice în timpul
rulării (schimbând celula cu inimă 0 în celulă goală 2 atunci când Pac-Man o intersectează), fără a
reîncărca resurse masive în memorie. E o metodă mult mai eficientă de a organiza lucrurile și îmi
permite o modularitate crescută.

La partea de aspect, am definit în config.h o structură și constante RGBA care controlează schema
cromatică a jocului. Am implementat o estetică personalizată bazată pe o paletă elegantă. Dacă vreau
să schimb tema grafică, modific doar în acel fișier central și se actualizează automat toate elementele. În
plus, interfața grafică interactivă (ecranul de Game Over) folosește structuri de tip Rectangle. Butoanele
de „Retry” și „Quit” monitorizează poziția cursorului prin GetMousePosition() și folosește funcția
booleană IsPointInsideRect() pentru a detecta evenimentele de tip click, permițând o resetare completă
a matricei hărții și a stării entităților la reînceperea jocului.


Evoluția jocului:
Proiectul a pornit inițial de la o variantă mai simplă axată pe structuri de date bidimensionale și logica de
deplasare pe coordonate discrete, o variantă în consolă ce s-a dovedit limitată din punct de vedere
vizual. Analizând nevoia de a oferi o experiență mai plăcută și modernă, am decis tranziția către
biblioteca grafică Raylib, fiind inspirată și de bunele practici observate la comunitățile de colegi din
domeniu. Această schimbare a reprezentat o provocare tehnică din cauza timpului limitat și a integrării
fizicii pe pixeli cu o rețea fixă de celule, dar a fost absolut necesară pentru a trece de la o interfață
rudimentară la una avansată, accelerată hardware. Pentru alegerea paletelor de culori și poziționarea
elementelor de UI pe ecranul scalat la 1120x1252 pixeli, m-am ghidat după principii estetice riguroase.
Resursele software m-au ajutat să înțeleg cum pot crea scheme de culori armonioase care să asigure un
echilibru corect între estetică și funcționalitate.

