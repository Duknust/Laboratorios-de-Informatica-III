/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3.util;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.SortedMap;
import org.duarteduarte.li3.data.AutoresAno;
import org.duarteduarte.li3.data.Autor;
import org.duarteduarte.li3.data.CoAutor;
import org.duarteduarte.li3.data.RedeAutores;

/**
 *
 * @author duarteduarte
 */
public class Util {

    private Util() {
    }

    public static Collection<Autor> listaAutores(RedeAutores ra) {
        Collection<Autor> aux = Factories.giveMeList();
        for (AutoresAno artsAno : ra.getRedes().values()) {
            for (Autor art : artsAno.getAutoresAno().values()) {
                aux.add(art);
            }
        }

        return aux;
    }

    /**
     * Devolve todos os autores com os totais de artigos escritos
     *
     * @param ra Rede de Autores (contém Map<ano,AutoresAno>)
     * @return
     */
    public static Collection<Autor> conjuntoAutores(RedeAutores todosAutores) {
        Map<String, Autor> autores = new HashMap<String, Autor>(100000);
        Autor tmp = null;
        int ioa;

        for (AutoresAno autoresAno : todosAutores.getRedes().values()) {
            for (Autor aux : autoresAno.getAutoresAno().values()) {
                //if (aux != null) {
                if (!autores.containsKey(aux.getNome())) {
                    autores.put(aux.getNome(), new Autor(aux));
                } else {
                    tmp = autores.get(aux.getNome());
                    tmp.addCoAutores(aux.getCoAutores());
                    tmp.incrementaContadores(aux.getNumCoautorias(), aux.getNumArtigosSolo());
                }
            }
        }

        return autores.values();
    }

    /**
     * Devolve todos os autores com os totais de artigos escritos
     *
     * @param ra Rede de Autores (contém Map<ano,AutoresAno>)
     * @return
     */
    public static Collection<Autor> conjuntoAutores(RedeAutores todosAutores, int anoIni, int anoFim) {
        Map<String, Autor> autores = new HashMap<String, Autor>(100000);
        Autor tmp = null;
        int ioa;

        for (AutoresAno autoresAno : ((SortedMap<Integer, AutoresAno>) todosAutores.getRedes()).subMap(anoIni, anoFim + 1).values()) {
            for (Autor aux : autoresAno.getAutoresAno().values()) {
                //if (aux != null) {
                if (!autores.containsKey(aux.getNome())) {
                    autores.put(aux.getNome(), new Autor(aux));
                } else {
                    tmp = autores.get(aux.getNome());
                    tmp.addCoAutores(aux.getCoAutores());
                    tmp.incrementaContadores(aux.getNumCoautorias(), aux.getNumArtigosSolo());
                }
            }
        }

        return autores.values();
    }

    public static Collection<Autor> everythingButAutor(String nome, Collection<Autor> col) {
        List<Autor> toKeep = Factories.giveMeList();

        for (Iterator<Autor> it = col.iterator(); it.hasNext();) {
            Autor tmp = it.next();
            if (!tmp.getNome().equals(nome)) {
                toKeep.add(tmp);
            }
        }

        return toKeep;
    }

    public static Collection<CoAutor> everythingButCoautor(String nome, Collection<CoAutor> col) {
        List<CoAutor> toKeep = Factories.giveMeList();

        for (Iterator<CoAutor> it = col.iterator(); it.hasNext();) {
            CoAutor tmp = it.next();
            if (!tmp.getNome().equals(nome)) {
                toKeep.add((CoAutor) tmp.clone());
            }
        }

        return toKeep;
    }
}
