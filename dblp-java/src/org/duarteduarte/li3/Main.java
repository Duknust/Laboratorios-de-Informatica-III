/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3;

import org.duarteduarte.li3.util.Factories;
import org.duarteduarte.li3.processing.FileHandling;
import java.util.Iterator;
import java.util.Map;
import java.util.List;
import java.util.StringTokenizer;
import org.duarteduarte.li3.data.Artigo;
import org.duarteduarte.li3.data.Autor;
import org.duarteduarte.li3.processing.Storage;
import org.duarteduarte.li3.processing.Statistics;

/**
 *
 * @author duarteduarte
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here;
        Storage store = new Storage();
        store.setFileName("publicx.txt");
        Statistics statistics = new Statistics();
        int linhaNum=0;
//        store.testAutores();
//        try {
//            FileHandling.writeToFile(store.getAutoresMap());
//            store.setAutoresMap(FileHandling.readFromFile());
//        } catch (IOException ioe) {
//            System.out.println("IOE: " + ioe.getMessage());
//        } catch (ClassNotFoundException cnfe) {
//            System.out.println("CNFE: " + cnfe.getMessage());
//        }

        
        List<String> linhas = FileHandling.leLinhasScanner("/Users/duarteduarte/Desktop/publicx.txt");
        int i = 0;

        Iterator<String> linhasIt = linhas.iterator();
        while (linhasIt.hasNext()) {
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
        
        
        //System.out.println("Autores: " + store.getRedeAutores().toString());
        //System.out.println("Numero Artigos: " + store.getArtigosAno(2003).getNumeroArtigos());
        System.out.println("pergunta1.1. -----> "+ statistics.pergunta11(store.getRedeAutores()));
        System.out.println(statistics.pergunta13(store.getRedeAutores()));
        System.out.println(statistics.pergunta12(store.getRedeAutores()));
    }

    public int max(List<Integer> lista) {
        int res = Integer.MIN_VALUE;

        for (Iterator<Integer> it = lista.iterator(); it.hasNext();) {
            int x = it.next();
            res = x > res ? x : res;
        }

        return res;
    }
}
