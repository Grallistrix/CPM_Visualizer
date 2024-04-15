import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Zdarzenie {
    String Nazwa;
    int Czas;
    List<String> Poprzednicy;
    List<String> Nastepcy;
    int EarlyStart;
    int EarlyFinish;
    int LastStart;
    int LastFinish;
    int Rezerwa;

    public Zdarzenie(String Nazwa, int Czas, List<String> Poprzednicy) {
        this.Nazwa = Nazwa;
        this.Czas = Czas;
        this.Poprzednicy = Poprzednicy;
        this.Nastepcy = new ArrayList<>();
        this.EarlyStart = 0;
        this.EarlyFinish = Czas;
        this.LastStart = 0;
        this.LastFinish = 0;
        this.Rezerwa = 0;
    }

    @Override
    public String toString() {
        return "Zdarzenie " + Nazwa + " Czas: " + Czas + "\n"
                + "ES: " + EarlyStart + " EF: " + EarlyFinish + "\n"
                + "LS: " + LastStart + " LF: " + LastFinish + "\n"
                + "Rezerwa: " + Rezerwa + "\n"
                + "Poprzednicy: " + Poprzednicy + "\n"
                + "Nastepcy: " + Nastepcy + "\n";
    }
}


public class CPMScheduler {
    private static List<Zdarzenie> tablicaZdarzen = new ArrayList<>();
    private static List<String> keys = new ArrayList<>();
    private static Map<String, Zdarzenie> mapaZdarzen = new HashMap<>();

    private static void LogikaForward() {
        for (Zdarzenie xx : mapaZdarzen.values()) {
            if (xx.Poprzednicy.isEmpty()) {
                xx.EarlyStart = 0;
                xx.EarlyFinish = xx.Czas;
                continue;
            }
            int tempEF = -1;
            for (String klucz : xx.Poprzednicy) {
                Zdarzenie it = mapaZdarzen.get(klucz);
                if (it.EarlyFinish > tempEF) {
                    tempEF = it.EarlyFinish;
                }
            }
            xx.EarlyStart = tempEF;
            xx.EarlyFinish = tempEF + xx.Czas;
        }
    }

    private static void FindNastepcy() {
        for (Zdarzenie xx : mapaZdarzen.values()) {
            if (!xx.Poprzednicy.isEmpty()) {
                for (String klucz : xx.Poprzednicy) {
                    Zdarzenie it = mapaZdarzen.get(klucz);
                    it.Nastepcy.add(xx.Nazwa);
                }
            }
        }
    }

    private static void LogikaBackwards() {
        int totalTime = 0;
        for (Zdarzenie xx : mapaZdarzen.values()) {
            keys.add(xx.Nazwa);
            if (xx.EarlyFinish > totalTime) {
                totalTime = xx.EarlyFinish;
            }
        }
        java.util.Collections.reverse(keys);
        for (String Zdarz : keys) {
            Zdarzenie it = mapaZdarzen.get(Zdarz);
            if (it.Nastepcy.isEmpty()) {
                it.LastFinish = totalTime;
            } else {
                int tempLF = totalTime;
                for (String klucz : it.Nastepcy) {
                    Zdarzenie itTemp = mapaZdarzen.get(klucz);
                    if (tempLF > itTemp.LastStart) {
                        tempLF = itTemp.LastStart;
                    }
                }
                it.LastFinish = tempLF;
            }
            it.LastStart = it.LastFinish - it.Czas;
            it.Rezerwa = it.LastFinish - it.EarlyFinish;
        }
    }

    private static String WyznaczCPM() {
        StringBuilder CPM_Path = new StringBuilder();
        java.util.Collections.reverse(keys);
        for (String Zdarzenie : keys) {
            Zdarzenie it = mapaZdarzen.get(Zdarzenie);
            if (it.Rezerwa == 0) {
                CPM_Path.append(it.Nazwa);
            }
        }
        return CPM_Path.toString();
    }

    public static void main(String[] args) {

        /*
         * 

         Zdarzenie A = new Zdarzenie("A", 3, new ArrayList<>());
         Zdarzenie B = new Zdarzenie("B", 4, new ArrayList<>(List.of("A")));
         Zdarzenie C = new Zdarzenie("C", 2, new ArrayList<>(List.of("A")));
         Zdarzenie D = new Zdarzenie("D", 5, new ArrayList<>(List.of("B")));
         Zdarzenie E = new Zdarzenie("E", 1, new ArrayList<>(List.of("C")));
         Zdarzenie F = new Zdarzenie("F", 2, new ArrayList<>(List.of("C")));
         Zdarzenie G = new Zdarzenie("G", 4, new ArrayList<>(List.of("D", "E")));
         Zdarzenie H = new Zdarzenie("H", 3, new ArrayList<>(List.of("F", "G")));
         tablicaZdarzen.add(A);
         tablicaZdarzen.add(B);
         tablicaZdarzen.add(C);
         tablicaZdarzen.add(D);
         tablicaZdarzen.add(E);
         tablicaZdarzen.add(F);
         tablicaZdarzen.add(G);
         tablicaZdarzen.add(H);
         */
        Zdarzenie A = new Zdarzenie("A", 7, new ArrayList<>());
        Zdarzenie B = new Zdarzenie("B", 9, new ArrayList<>());
        Zdarzenie C = new Zdarzenie("C", 12, new ArrayList<>(List.of("A")));
        Zdarzenie D = new Zdarzenie("D", 8, new ArrayList<>(List.of("A", "B")));
        Zdarzenie E = new Zdarzenie("E", 9, new ArrayList<>(List.of("D")));
        Zdarzenie F = new Zdarzenie("F", 6, new ArrayList<>(List.of("C", "E")));
        Zdarzenie G = new Zdarzenie("G", 5, new ArrayList<>(List.of("E")));
        tablicaZdarzen.add(A);
        tablicaZdarzen.add(B);
        tablicaZdarzen.add(C);
        tablicaZdarzen.add(D);
        tablicaZdarzen.add(E);
        tablicaZdarzen.add(F);
        tablicaZdarzen.add(G);

        int i = 0;
        for (Zdarzenie x : tablicaZdarzen) {
            mapaZdarzen.put(String.valueOf((char) (65 + i)), x);
            i++;
        }

        LogikaForward();
        FindNastepcy();
        LogikaBackwards();
        for (Zdarzenie xx : mapaZdarzen.values()) {
            System.out.println(xx);
        }

        System.out.println("Path to CPM: " + WyznaczCPM());
    }
}
