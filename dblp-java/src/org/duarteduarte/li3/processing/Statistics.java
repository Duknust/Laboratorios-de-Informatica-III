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
import java.util.List;
import java.util.Map.Entry;
import java.util.Set;
import java.util.SortedMap;
import java.util.TreeMap;
import org.duarteduarte.li3.data.AutoresAno;
import org.duarteduarte.li3.data.Autor;
import org.duarteduarte.li3.data.RedeAutores;
import org.duarteduarte.li3.util.Factories;
import org.duarteduarte.li3.util.Util;

/**
 *
 * @author duarteduarte
 */
public class Statistics {

// grupo1
    // pergunta 1.1
    public String pergunta11(RedeAutores ra) {
        int numeroArtigosLidos = numeroArtigosLidos(ra);
        String nomeFicheiro = ra.getNomeFicheiro();
        String totalNomes = totalNomes(ra);
        int anoMax = ra.getAnoMaximo();
        int anoMin = ra.getAnoMinimo();

        return new StringBuilder().append("No " + nomeFicheiro + " foram lidos " + numeroArtigosLidos + " artigos, num total de " + totalNomes + "e o intervalo fechado de [" + anoMin + "," + anoMax + "]").toString();
    }

    public int numeroArtigosLidos(RedeAutores rede) {
        int res = 0;

        if (rede == null) {
            throw new IllegalArgumentException("A rede não pode ser vazia.");
        }

        for (AutoresAno r : rede.getAutores().values()) {
            res += r.getNumeroArtigos();
        }
        return res;
    }

    public String totalNomes(RedeAutores rede) {
        List<String> autores = Factories.giveMeList();

        if (rede == null) {
            throw new IllegalArgumentException("A rede não pode ser vazia.");
        }

        for (AutoresAno aa : rede.getAutores().values()) {
            autores.addAll(aa.getAutoresAno().keySet());
        }

        return "" + rede.getTotalAutores() + " nomes, destes " + autores.size() + " sao distintos, ";
    }

    // pergunta 1.2
    public String pergunta12(RedeAutores ra) {
        // número total de autores, número total de artigos de um 
        // único autor, número total de autores que apenas publicaram a solo (sem coautores) e número total de
        // autores que nunca publicaram a solo;

        List<Integer> res = null;

        if (ra == null) {
            throw new IllegalArgumentException("A rede não pode ser vazia.");
        }
        res = artigosUnicoAutor(ra);
        StringBuilder sb = new StringBuilder();
        sb.append("Total de autores: ");
        sb.append(res.get(0) + "\n");
        sb.append("Numero de artigos com um autor: ");
        sb.append(res.get(1) + "\n");
        sb.append("Autores com obras unicamente a solo: ");
        sb.append(res.get(2) + "\n");
        sb.append("Autores que não têm obras a solo: ");
        sb.append(res.get(3) + "\n");

        return sb.toString();
    }

    private List<Integer> artigosUnicoAutor(RedeAutores ra) {
        int numeroArtigosSolo = 0;
        List<Integer> res = new ArrayList<Integer>(4);
        Collection<Autor> autoresSolo = Factories.giveMeSet();
        Collection<Autor> autoresNaoSolo = Util.conjuntoAutores(ra);
        int totalAutores = autoresNaoSolo.size();

        for (AutoresAno r : ra.getAutores().values()) {
            for (Autor autor : r.getAutoresAno().values()) {
                if (autor != null) {
                    if (autor.getnArtigosSolo() > 0) {
                        numeroArtigosSolo += autor.getnArtigosSolo();
                        if (autor.getNumCoautorias() == 0) {
                            autoresSolo.add(autor);
                        }
                    }
                }
            }
        }

        autoresNaoSolo.removeAll(autoresSolo);

        res.add(totalAutores);
        res.add(numeroArtigosSolo);
        res.add(autoresSolo.size());
        res.add(autoresNaoSolo.size());

        return res;
    }

    private int totalAutores(RedeAutores ra) {
        int res = 0;
        Collection<Autor> aux = Util.conjuntoAutores(ra);
        return aux.size();
    }

    //pergunta 1.3
    public String pergunta13(RedeAutores ra) {
        if (ra == null) {
            throw new IllegalArgumentException("A rede não pode ser vazia.");
        }

        StringBuilder sb = new StringBuilder();
        StringBuilder sbHtml = new StringBuilder();
        SortedMap<Integer, AutoresAno> ordenado = new TreeMap<Integer, AutoresAno>(ra.getAutores());

        sb.append("+------+------------+\n");
        sbHtml.append("<table border=\"1\">\n");//tabela html
        for (Entry<Integer, AutoresAno> e : ordenado.entrySet()) {
            sb.append("| " + e.getKey() + " | " + e.getValue().getNumeroArtigos() + " | \n");
            sbHtml.append("<tr><td>" + e.getKey() + "</td><td>" + e.getValue().getNumeroArtigos() + "</td></tr>\n");//tabela html
        }
        sb.append("+------+------------+\n");
        sbHtml.append("</table>\n");//tabela html
        //tabela html
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream("/Users/duarteduarte/tabela1.2.html", false);
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


        System.out.println(sbHtml.toString());

        return sb.toString();
    }

// grupo 2
    //pergunta 2.1
    // a) O TOP X de número de publicações (ordem crescente dos nomes) sendo X dado pelo utilizador;
    public int pergunta21a(RedeAutores ra) {


        return 0;
    }

    // b) O TOP X de co-autorias, ou seja, os X pares de autores e respectivo número de artigos, com mais artigos publicados 
    // em co-autoria, sendo X dado pelo utilizador (ordem decrescente do número de artigos);
    public int pergunta21b(RedeAutores ra) {

        return 0;
    }

    // c) A listagem, por ordem alfabética crescente, de todos os co-autores comuns aos autores de uma dada lista de 
    // nomes a introduzir pelo utilizador;
    public int pergunta21c(RedeAutores ra) {

        return 0;
    }

    // d) A listagem dos nomes dos autores que publicaram artigos em todos os anos do intervalo de anos dado 
    public int pergunta21d(RedeAutores ra) {

        return 0;
    }

    //pergunta 2.2
    // a) Contar o número de linhas em duplicado no ficheiro publicx.txt (o ficheiro deverá ser relido no momento 
    // da realização desta consulta); 
    public int pergunta22a(RedeAutores ra) {

        return 0;
    }

    // b) Tabela com todos os autores e respectivas redes de co-autores, mas apenas para associações em que o número 
    // de co-autores seja inferior a um número X dado (deve ser devolvida a estrutura completa que satisfaz os requisitos)
    public int pergunta22b(RedeAutores ra) {

        return 0;
    }
}
