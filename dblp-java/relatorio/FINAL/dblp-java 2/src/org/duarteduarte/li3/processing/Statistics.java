/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3.processing;

import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.SortedMap;
import java.util.TreeMap;
import java.util.TreeSet;
import org.duarteduarte.li3.data.Autor;
import org.duarteduarte.li3.data.AutoresAno;
import org.duarteduarte.li3.data.CoAutor;
import org.duarteduarte.li3.data.RedeAutores;
import org.duarteduarte.li3.util.Factories;
import org.duarteduarte.li3.util.Util;

/**
 *
 * @author duarteduarte
 */
public class Statistics {

    private RedeAutores ra;
    private final Collection<Autor> conjuntoAutores;

    public Statistics(RedeAutores ra) {
        this.ra = ra;
        this.conjuntoAutores = Util.conjuntoAutores(ra);
    }

    public void setRedeAutores(RedeAutores ra) {
        this.ra = ra;
    }

    /*public void setTodosAutores(List<Autor> todosAutores) {
     this.conjuntoAutores = Util.conjuntoAutores(todosAutores);
     }*/
// grupo1
    // pergunta 1.1
    public String pergunta11() {
        int numeroArtigosLidos = numeroArtigosLidos();
        String nomeFicheiro = this.ra.getNomeFicheiro();
        int totalNomes = this.ra.getTotalAutores();
        int totalNomesDistintos = totalNomes();
        TreeSet<Integer> anos = new TreeSet<Integer>(ra.getRedes().keySet());
        int anoMax = anos.last();
        int anoMin = anos.first();

        return ("No " + nomeFicheiro + " foram lidos " + numeroArtigosLidos + " artigos, num total de " + totalNomes + " nomes, destes " + +totalNomesDistintos + " sao distintos, e o intervalo fechado de [" + anoMin + "," + anoMax + "]").toString();
    }

    public int numeroArtigosLidos() {
        int res = 0;

        if (this.ra == null) {
            throw new IllegalArgumentException("A rede n√£o pode ser vazia.");
        }

        for (AutoresAno r : this.ra.getRedes().values()) {
            res += r.getNumeroArtigos();
        }
        return res;
    }

    public int totalNomes() {
        ArrayList<String> autores = new ArrayList<String>(100000);

        if (this.ra == null) {
            throw new IllegalArgumentException("A rede n√£o pode ser vazia.");
        }

        for (AutoresAno aa : this.ra.getRedes().values()) {
            autores.addAll(aa.getAutoresAno().keySet());
        }

        return new HashSet<String>(autores).size();
    }

    // pergunta 1.2
    public String pergunta12() {
        // n√∫mero total de autores, n√∫mero total de artigos de um 
        // √∫nico autor, n√∫mero total de autores que apenas publicaram a solo (sem coautores) e n√∫mero total de
        // autores que nunca publicaram a solo;

        List<Integer> res = null;

        if (ra == null) {
            throw new IllegalArgumentException("A rede n√£o pode ser vazia.");
        }
        res = artigosUnicoAutor();
        StringBuilder sb = new StringBuilder();
        sb.append("Total de autores: ");
        sb.append(res.get(0) + "\n");
        sb.append("Numero de artigos com um autor: ");
        sb.append(res.get(1) + "\n");
        sb.append("Autores com obras unicamente a solo: ");
        sb.append(res.get(2) + "\n");
        sb.append("Autores que n√£o t√™m obras a solo: ");
        sb.append(res.get(3) + "\n");

        return sb.toString();
    }

    private List<Integer> artigosUnicoAutor() {
        int numeroArtigosSolo = 0;
        List<Integer> res = new ArrayList<Integer>(4);
        int totalAutores = this.totalNomes();
        Set<Autor> autoresSolo = Factories.giveMeSet();
        Collection<Autor> autoresNaoSolo = new ArrayList<Autor>(this.conjuntoAutores.size());
        autoresNaoSolo.addAll(this.conjuntoAutores);
        Set<Autor> autoresSoloECoautoria = Factories.giveMeSet();

        for (Autor autor : autoresNaoSolo) {
            if (autor != null) {
                if (autor.getNumArtigosSolo() > 0) {
                    numeroArtigosSolo += autor.getNumArtigosSolo();
                    if (autor.getNumCoautorias() == 0) {
                        autoresSolo.add(autor);
                    } else {
                        autoresSoloECoautoria.add(autor);
                    }
                }
            }
        }

        autoresNaoSolo.removeAll(autoresSolo);
        autoresNaoSolo.removeAll(autoresSoloECoautoria);

        res.add(totalAutores);
        res.add(numeroArtigosSolo);
        res.add(autoresSolo.size());
        res.add(autoresNaoSolo.size());

        return res;
    }

    private int totalAutores() {
        //int res = 0;
        Collection<Autor> aux = this.conjuntoAutores;
        return aux.size();
    }

    //pergunta 1.3
    public String pergunta13() {
        if (this.ra == null) {
            throw new IllegalArgumentException("A rede n√£o pode ser vazia.");
        }

        StringBuilder sb = new StringBuilder();
        StringBuilder sbHtml = new StringBuilder();
        SortedMap<Integer, AutoresAno> ordenado = new TreeMap<Integer, AutoresAno>(this.ra.getRedes());

        sb.append("+------+------------+\n");
        sbHtml.append("<table border=\"1\">\n");//tabela html
        for (Entry<Integer, AutoresAno> e : ordenado.entrySet()) {
            sb.
                    append("| ").
                    append(e.getKey()).
                    append(" | ").
                    append(e.getValue().getNumeroArtigos()).
                    append(" | \n");
            sbHtml.
                    append("<tr><td>").
                    append(e.getKey()).
                    append("</td><td>").
                    append(e.getValue().getNumeroArtigos()).
                    append("</td></tr>\n");//tabela html
        }
        sb.append("+------+------------+\n");
        sbHtml.append("</table>\n");//tabela html
        //tabela html
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream("tabela1.2.html", false);
            fos.write(sbHtml.toString().getBytes(Charset.forName("UTF-8")));
        } catch (IOException ioe) {
        } finally {
            if (fos != null) {
                try {
                    fos.flush();
                    fos.close();
                } catch (IOException ioe) {
                }
            }
        }

       // System.out.println(sbHtml.toString());

        return sb.toString();
    }

// grupo 2
    //pergunta 2.1
    // a) O TOP X de número de publicações (ordem crescente dos nomes) sendo X dado pelo utilizador;
    public String pergunta21a(int x, int anoIni, int anoFim) {
        List<TopXEntry> topX = new ArrayList<TopXEntry>(x);
        this.initTopX(topX, x);
        //SortedMap<Integer, AutoresAno> aux = ((SortedMap<Integer, AutoresAno>) this.ra.getRedes()).subMap(anoIni, anoFim + 1);

        Collection<Autor> autoresReunidos = Util.conjuntoAutores(ra, anoIni, anoFim);
        for (Autor aut : autoresReunidos) {
            avaliaAutor(aut, topX);
        }

        TreeSet<TopXEntry> ordenado = new TreeSet<TopXEntry>();
        if (!topX.isEmpty() && !topX.contains(null)) {
            ordenado.addAll(topX);
        } else {
            for (TopXEntry txe : topX) {
                if (txe != null) {
                    ordenado.add(txe);
                }
            }
        }

        return ordenado.toString();
    }

    private void initTopX(List<?> topx, int x) {
        for (int i = 0; i < x; i++) {
            topx.add(i, null);
        }
    }

    private void avaliaAutor(Autor autor, List<TopXEntry> topX) {
        TopXEntry toAdd = new TopXEntry(autor.getNome(), autor.totalArtigos());
        int i;
        boolean added = false;

        if (topX.contains(null)) {
            topX.set(topX.indexOf(null), toAdd);
        } else {
            for (i = 0; i < topX.size() && !added; i++) {
                if (topX.get(i).compareTo(toAdd) < 0) {
                    topX.set(i, toAdd);
                    added = true;
                }
            }
        }
    }

    // b) O TOP X de co-autorias, ou seja, os X pares de autores e respectivo n√∫mero de artigos, com mais artigos publicados 
    // em co-autoria, sendo X dado pelo utilizador (ordem decrescente do n√∫mero de artigos);
    public String pergunta21b(int x, int anoIni, int anoFim) {
        Collection<Autor> autoresReunidos = Util.conjuntoAutores(this.ra, anoIni, anoFim);
        List<TopXYEntry> topX = new ArrayList<TopXYEntry>(x);
        this.initTopX(topX, x);

        for (Autor aut : autoresReunidos) {
            avaliaCoAutoria(aut, topX);
        }

        TreeSet<TopXYEntry> ordenado = new TreeSet<TopXYEntry>();
        if (!topX.isEmpty() && !topX.contains(null)) {
            ordenado.addAll(topX);
        } else {
            for (TopXYEntry txe : topX) {
                if (txe != null) {
                    ordenado.add(txe);
                }
            }
        }

        return ordenado.toString();
    }

    private void avaliaCoAutoria(Autor autor, List<TopXYEntry> topX) {
        for (CoAutor ca : autor.getCoAutores()) {
            TopXYEntry toAdd = new TopXYEntry(autor.getNome(), ca.getNome(), ca.getArtigosComum());

            int i;
            boolean added = false;

            if (topX.contains(null)) {
                topX.set(topX.indexOf(null), toAdd);
            } else {
                for (i = 0; i < topX.size() && !added; i++) {
                    if (topX.get(i).compareTo(toAdd) < 0) {
                        topX.set(i, toAdd);
                        added = true;
                    }
                }
            }
        }
    }

    // c) A listagem, por ordem alfab√©tica crescente, de todos os co-autores comuns aos autores de uma dada lista de 
    // nomes a introduzir pelo utilizador;
    public Collection<CoAutor> pergunta21c(List<String> lista, int anoIni, int anoFim) {
        TreeSet<CoAutor> res = new TreeSet<CoAutor>();
        TreeSet<CoAutor> tmp = new TreeSet<CoAutor>();
        TreeSet<CoAutor> toRemove = new TreeSet<CoAutor>();
        Map<String, Autor> aa;

        SortedMap<Integer, AutoresAno> intervalo = ((SortedMap<Integer, AutoresAno>) this.ra.getRedes()).subMap(anoIni, anoFim + 1);

        if (lista == null || lista.isEmpty() || lista.size() < 2) {
            throw new IllegalArgumentException("Lista vazia ou com menos de 2 elementos");
        }
        for (Integer i : intervalo.keySet()) {
            if (intervalo.containsKey(i) && (aa = intervalo.get(i).getAutoresAno()) != null) {
                if (aa.containsKey(lista.get(0))) {
                    Collection<CoAutor> aux = aa.get(lista.get(0)).getCoAutores();
                    if (aux != null) {
                        res.addAll(aux);
                    }
                }
            }
        }

        for (String s : lista.subList(1, lista.size())) {
            for (Integer i : intervalo.keySet()) {
                AutoresAno aano = intervalo.get(i);
                if (aano != null && aano.getAutoresAno().containsKey(s)) {
                    Collection<CoAutor> aux;
                    if ((aux = aano.getAutoresAno().get(s).getCoAutores()) != null) {
                        tmp.addAll(aux);
                    }
                }
            }
        }

        for (CoAutor ca : tmp) {
            if (!res.contains(ca)) {
                toRemove.add(ca);
            }
        }

        res.removeAll(toRemove);
        for (String s : lista) {
            res.remove(new CoAutor(s));
        }
        return res;
    }

    // d) A listagem dos nomes dos autores que publicaram artigos em todos os anos do intervalo de anos dado 
    public String pergunta21d(int anoIni, int anoFim) {
        Set<String> autoresRes = new TreeSet<String>();
        Set<String> autores2ano = new TreeSet<String>();
        Set<String> toRemove = new TreeSet<String>();
        //PODE SER NULLO! VERIFICAR! 
        SortedMap<Integer, AutoresAno> intervalo = ((SortedMap<Integer, AutoresAno>) this.ra.getRedes()).subMap(anoIni, anoFim + 1);

        while (!intervalo.containsKey(anoIni) && anoIni <= anoFim) {
            anoIni++;
        }
        if (intervalo.containsKey(anoIni)) {
            autoresRes.addAll(intervalo.get(anoIni).getAutoresAno().keySet());

            for (int i = anoIni + 1; i <= anoFim; i++) {
                AutoresAno tmp = intervalo.get(i);
                if (tmp != null) {
                    autores2ano.addAll(tmp.getAutoresAno().keySet());
                    for (String s : autoresRes) {
                        if (!autores2ano.contains(s)) {
                            toRemove.add(s);
                        }
                    }
                    autores2ano.clear();
                }
            }

            autoresRes.removeAll(toRemove);
        }

        return autoresRes.toString();
    }

    //pergunta 2.2
    // a) Contar o n√∫mero de linhas em duplicado no ficheiro publicx.txt (o ficheiro dever√° ser relido no momento 
    // da realiza√ß√£o desta consulta); 
    public int pergunta22a() {
        List<String> linhas = FileHandling.leLinhasScanner(this.ra.getNomeFicheiro());
        int totalLidas = linhas.size();
        int semRepetidos = new TreeSet<String>(linhas).size();
        return totalLidas - semRepetidos;
    }

    // b) Tabela com todos os autores e respectivas redes de co-autores, mas apenas para associa√ß√µes em que o n√∫mero 
    // de co-autores seja inferior a um n√∫mero X dado (deve ser devolvida a estrutura completa que satisfaz os requisitos)
    public String pergunta22b(int x, int anoIni, int anoFim) {
        HashSet<Autor> res = new HashSet<Autor>();
        Collection<Autor> toTrade = Util.conjuntoAutores(this.ra, anoIni, anoFim);

        for (Autor aut : toTrade) {
            if (aut.getNumeroCoAutores() < x) {
                res.add(aut);
            }
        }

        return res.toString();
    }

    private class TopXEntry implements Comparable<TopXEntry> {

        @Override
        public int compareTo(TopXEntry txe) {
            int res;
            if (this.numArtigos == txe.getNumArtigos()) {
                res = (this.nomeAutor.compareTo(txe.getNomeAutor()));
            } else if (this.numArtigos < txe.getNumArtigos()) {
                res = -1;
            } else {
                res = 1;
            }
            return res;
        }
        private String nomeAutor;
        private int numArtigos = 0;

        String getNomeAutor() {
            return this.nomeAutor;
        }

        int getNumArtigos() {
            return this.numArtigos;
        }

        public TopXEntry(String nomeAutor, int numArtigos) {
            this.nomeAutor = nomeAutor;
            this.numArtigos = numArtigos;
        }

        @Override
        public String toString() {
            return "nomeAutor=" + this.nomeAutor + ", numArtigos=" + this.numArtigos + '\n';
        }
    }

    private class TopXYEntry implements Comparable<TopXYEntry> {

        private String nomeAutor1;
        private String nomeAutor2;
        private int numArtigosComuns = 0;

        @Override
        public int compareTo(TopXYEntry txe) {
            int res = 0;
            if (this.numArtigosComuns == txe.getNumArtigosComuns()
                    && ((this.nomeAutor1.equals(txe.getNomeAutor1()) && this.nomeAutor2.equals(txe.getNomeAutor2()))
                    || ((this.nomeAutor1.equals(txe.getNomeAutor2()) && this.nomeAutor2.equals(txe.getNomeAutor1()))))) {
                res = 0;
            } else if (this.numArtigosComuns < txe.getNumArtigosComuns()) {
                res = -1;
            } else {
                res = 1;
            }
            return res;
        }

        String getNomeAutor1() {
            return this.nomeAutor1;
        }

        String getNomeAutor2() {
            return this.nomeAutor2;
        }

        int getNumArtigosComuns() {
            return this.numArtigosComuns;
        }

        public TopXYEntry(String nomeAutor1, String nomeAutor2, int numArtigos) {
            this.nomeAutor1 = nomeAutor1;
            this.nomeAutor2 = nomeAutor2;
            this.numArtigosComuns = numArtigos;
        }

        @Override
        public String toString() {
            return "nomeAutor=" + this.nomeAutor1 + ", nomeAutor=" + this.nomeAutor2 + ", numArtigos=" + this.numArtigosComuns + '\n';
        }
    }
}
