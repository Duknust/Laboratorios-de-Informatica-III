package org.duarteduarte.li3;



 

import java.io.*;
import org.duarteduarte.li3.util.Factories;
import org.duarteduarte.li3.processing.FileHandling;
import java.util.Iterator;
import java.util.List;
import java.util.StringTokenizer;
import java.util.concurrent.TimeUnit;
import org.duarteduarte.li3.data.Artigo;
import org.duarteduarte.li3.processing.Storage;
import org.duarteduarte.li3.processing.Statistics;
import static java.lang.System.out;
import java.util.Arrays;
import java.util.Scanner;





public class Main implements Serializable{

    
    
private static Storage store = new Storage();

private static Statistics statistics;
    

    
private static Scanner scan = new Scanner(System.in);
    
    


    public static void main(String[] args) {

        
        
        
//        store.setFileName("publicx.txt");
//        store.setFileName("publicx_x4.txt");
        store.setFileName("publicx_x8.txt");
        
       //List<String> linhas = FileHandling.leLinhasScanner("publicx_x8.txt");
       long inicio = System.nanoTime();
       LerFicheiroTXT();
       long fim = System.nanoTime();
       out.printf("%1$.5f ",(double)(fim - inicio)/1.0E09);
       

       
        
       String str = "Loris Nanni,Alessandra Lumini";
        List<String> items = Arrays.asList(str.split("\\s*,\\s*"));
        
        
       inicio = System.nanoTime();
       statistics.pergunta11();
       fim = System.nanoTime();
       out.printf("%1$.5f ",(double)(fim - inicio)/1.0E09);
       
       
        
       inicio = System.nanoTime();
       statistics.pergunta12();
       fim = System.nanoTime();
       out.printf("%1$.5f ",(double)(fim - inicio)/1.0E09);
       
       
        
       inicio = System.nanoTime();
       statistics.pergunta13();
       fim = System.nanoTime();
       out.printf("%1$.5f ",(double)(fim - inicio)/1.0E09);
       
       
        
       inicio = System.nanoTime();
       statistics.pergunta21a(6,1960,2010);
       fim = System.nanoTime();
       out.printf("%1$.5f ",(double)(fim - inicio)/1.0E09);
       
        
        
       inicio = System.nanoTime();
       statistics.pergunta21b(6,1960,2010);
       fim = System.nanoTime();
       out.printf("%1$.5f ",(double)(fim - inicio)/1.0E09);
       
       
        
       inicio = System.nanoTime();
       statistics.pergunta21c(items,1960,2010);
       fim = System.nanoTime();
       out.printf("%1$.5f ",(double)(fim - inicio)/1.0E09);
       
       
        
       inicio = System.nanoTime();
       statistics.pergunta21d(1960,2010);
       fim = System.nanoTime();
       out.printf("%1$.5f ",(double)(fim - inicio)/1.0E09);
       
       
        
       inicio = System.nanoTime();
       statistics.pergunta22a();
       fim = System.nanoTime();
       out.printf("%1$.5f ",(double)(fim - inicio)/1.0E09);
       
       
        
       inicio = System.nanoTime();
       statistics.pergunta22b(6,1960,2010);
       fim = System.nanoTime();
       out.printf("%1$.5f ",(double)(fim - inicio)/1.0E09);
       
       

    }




    public static void main1(String[] args) {
        
        
        
/*    try {
   Thread.sleep(10000);
} catch(InterruptedException ex) {
    Thread.currentThread().interrupt();
}*/
        
        
        
        store.setFileName("publicx.txt");
        
        int escolha=50;
        
        
        
        
        while(escolha != 0){
            
             LimpaEcra();   
            
            System.out.println("## 1 - Ler    publicx.txt");
            System.out.println("## 2 - Ler    publicx.obj");
            System.out.println("## ---------------");
            System.out.println("## 0 - Sair");
            
            
            escolha = getInt();
            if(escolha <0 || escolha >2)
                System.out.println("Não é uma opção válida");
            else{LimpaEcra();
                switch(escolha)
                {
                    case(0):System.out.println("\n-----###_#_#_#_#_#_ | Aplicação Encerrou | _#_#_#_#_#_###-----\n");
                            break;
                    case(1):System.out.print("A Ler publicx.txt .");
                            LerFicheiroTXT();
                            MenuPerguntas();
                            break;
                    case(2):System.out.print("A Ler publicx.obj .");
                            LerFicheiroOBJ();
                            MenuPerguntas();
                            break;
                    
                        
                    
                }}
            
            
            
                    
            
        }
        
        
        
        
        
        /*
        long millis = System.currentTimeMillis();
        statistics.pergunta11();
        System.out.println(System.currentTimeMillis()-millis);
        
        millis = System.currentTimeMillis();
        statistics.pergunta12();
        System.out.println(System.currentTimeMillis()-millis);
        
        millis = System.currentTimeMillis();
        statistics.pergunta13();
        System.out.println(System.currentTimeMillis()-millis);
        
        millis = System.currentTimeMillis();
        statistics.pergunta21a(10);
        System.out.println(System.currentTimeMillis()-millis);
        */
    }

    
    
    
    
    public static void MenuPerguntas() {
        
        int escolha=50;
        
        

        statistics = new Statistics(store.getRedeAutores());
        
        while(escolha != 0){
            
                
            
            System.out.println("\n## 1 - Pergunta 1.1");
            System.out.println("## 2 - Pergunta 1.2");
            System.out.println("## 3 - Pergunta 1.3");
            System.out.println("## 4 - Pergunta 2.1.a");
            System.out.println("## 5 - Pergunta 2.1.b");
            System.out.println("## 6 - Pergunta 2.1.c");
            System.out.println("## 7 - Pergunta 2.1.d");
            System.out.println("## 8 - Pergunta 2.2.a");
            System.out.println("## 9 - Pergunta 2.2.b");
            System.out.println("## ---------------");
            System.out.println("## 10- Gravar dados em publicx.obj");
            System.out.println("## 0 - Sair");
            
            
            escolha = getInt();
            if(escolha <0 || escolha >10)
                System.out.println("Não é uma opção válida");
            else{LimpaEcra();
                switch(escolha)
                {
                    case(0):System.out.println("\n-----###_#_#_#_#_#_ | Aplicação Encerrou | _#_#_#_#_#_###-----\n");
                            break;
                    case(1):System.out.println(statistics.pergunta11());
                            break;
                    case(2):System.out.println(statistics.pergunta12());
                            break;
                    case(3):System.out.println(statistics.pergunta13());
                            break;
                    case(4):int a=-10;System.out.println("TOP:");
                            while(a <1)
                                a = getInt();
                            int b=-10;System.out.println("Ano Inicial");
                            while(b <1)
                                b = getInt();
                            int c=-10;System.out.println("Ano Final");
                            while(c < b || c < 1)
                                c = getInt();
                            
                            System.out.println(statistics.pergunta21a(a,b,c));
                            break;
                    case(5):int a1=-10;System.out.println("TOP:");
                            while(a1 <1)
                                a1 = getInt();
                            int b1=-10;System.out.println("Ano Inicial");
                            while(b1 <1)
                                b1 = getInt();
                            int c1=-10;System.out.println("Ano Final");
                            while(c1 < b1 || c1 < 1)
                                c1 = getInt();
                            System.out.println(statistics.pergunta21b(a1,b1,c1));
                            break;
                    case(6):int b4=-10;System.out.println("Ano Inicial");
                            while(b4 <1)
                                b4 = getInt();
                            int c4=-10;System.out.println("Ano Final");
                            while(c4 < b4 || c4 < 1)
                                c4 = getInt();
                            System.out.println("Lista de autores separados por vírgulas:");
                            String str = scan.nextLine();
                            List<String> items = Arrays.asList(str.split("\\s*,\\s*"));
                            System.out.println(statistics.pergunta21c(items,b4,c4));
                            break;
                    case(7):int b2=-10;System.out.println("Ano Inicial");
                            while(b2 <1)
                                b2 = getInt();
                            int c2=-10;System.out.println("Ano Final");
                            while(c2 < b2 || c2 < 1)
                                c2 = getInt();
                            System.out.println(statistics.pergunta21d(b2,c2));
                            break;
                    case(8):System.out.println(statistics.pergunta22a());
                            break;
                    case(9):int a3=-10;System.out.println("Número Máximo de Coautores:");
                            while(a3 <1)
                                a3 = getInt();
                            int b3=-10;System.out.println("Ano Inicial");
                            while(b3 <1)
                                b3 = getInt();
                            int c3=-10;System.out.println("Ano Final");
                            while(c3 < b3 || c3 < 1)
                                c3 = getInt();
                            System.out.println(statistics.pergunta22b(a3,b3,c3));
                            break;
                    case(10):EscreverFicheiroOBJ();//Guardar
                            break;
                        
                }}
            
            
        }
        
        
        
        
        
        // TODO code application logic here;
        
        
        /*
        long millis = System.currentTimeMillis();
        statistics.pergunta11();
        System.out.println(System.currentTimeMillis()-millis);
        
        millis = System.currentTimeMillis();
        statistics.pergunta12();
        System.out.println(System.currentTimeMillis()-millis);
        
        millis = System.currentTimeMillis();
        statistics.pergunta13();
        System.out.println(System.currentTimeMillis()-millis);
        
        millis = System.currentTimeMillis();
        statistics.pergunta21a(10);
        System.out.println(System.currentTimeMillis()-millis);
        */
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    public int max(List<Integer> lista) {
        int res = Integer.MIN_VALUE;

        for (Iterator<Integer> it = lista.iterator(); it.hasNext();) {
            int x = it.next();
            res = x > res ? x : res;
        }

        return res;
    }
    
    
    
    
    
    
    
    
    
    public static boolean EscreverFicheiroOBJ() {
        
        
    try {
      File file = new File("publicx.obj");
      ObjectOutputStream output = null;
      
    
        output = new ObjectOutputStream(new FileOutputStream(file));
//        output.writeObject(statistics);
        output.writeObject(store);
        
        
            //output.writeObject(this);
        
       
        output.close(); 
        
        }catch (IOException x){
            
            
            System.out.println("Não deu para Gravar - Erro de IO");
            x.printStackTrace();
            return false;
        }catch(NullPointerException n){
            
            System.out.println("Não deu para Gravar - Erro de  NPE");
            return false;
        }
    return (true);

  }
    
    
    
    
    public static boolean LerFicheiroOBJ( ) {
        
        
        

    
        ObjectInputStream input;
        try{
         File file = new File("publicx.obj");
        input = new ObjectInputStream(new FileInputStream(file));
        
        
        
        
        //statistics=(Statistics)input.readObject();
 
        store=(Storage)input.readObject();
        
        
        input.close();
        }catch (IOException x){
              
            System.out.println("Não deu para Ler - Erro de IO");
            return false;
            
        }catch(ClassNotFoundException x){
            System.out.println("Não deu para Ler - Erro de Classes");
            return false;
        }
    return (true);

  }
    
    
    
    
    public static boolean LerFicheiroTXT( ) {
        
        
        

    
        
        List<String> linhas = FileHandling.leLinhasScanner(store.getFileName());
        
        int i = 0;
        int last = 0;
        
 
        
        Iterator<String> linhasIt = linhas.iterator();
        while (linhasIt.hasNext()) {
            
            if (i++ - last == 10000) {
                last=i;
                //System.out.print(".");
            }

            String linha = linhasIt.next();

            StringTokenizer st = new StringTokenizer(linha, ",");

            List<String> tokens = Factories.giveMeList();
            while (st.hasMoreTokens()) {
                tokens.add(st.nextToken());
            }

            String anoString = tokens.get(tokens.size() - 1).trim();
            int ano = 0;
            if (anoString.matches("^[0-9]+$")) {
                ano = Integer.parseInt(anoString);
            }
            // System.out.println(linhaNum++);
            tokens.remove(tokens.size() - 1);

            Iterator<String> autoresIt = tokens.iterator();
            Artigo tmp = new Artigo();
            while (autoresIt.hasNext()) {
                tmp.insereAutor(autoresIt.next().trim());
            }
            store.addArtigo(ano, tmp);
        }


        statistics = new Statistics(store.getRedeAutores());
        
        
    return (true);

  }
    
    
    
    static void LimpaEcra(){
        //System.out.print('\u000C');
    }  
    
    
    
    
    static int getInt(){
        out.print("->");
        String s = scan.nextLine();
        int a=-10;
        try{
            a=Integer.parseInt(s);
            
        }
        catch(NumberFormatException ex){
            System.out.println("Não é um número válido");
        }
        return a;
        
    }
    
    static double getDouble(){
        out.print("->");
        String s = scan.nextLine();
        double a=-10;
        try{
            a=Double.parseDouble(s);
            
        }
        catch(NumberFormatException ex){
            System.out.println("Não é um valor válido");
        }
        return a;
        
    }
    
    static String getString(){
        out.print("->");
        String s = scan.nextLine();
        
        return s;
        
    }
    
    
    
    
    
    
}
