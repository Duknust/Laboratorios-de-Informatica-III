/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3.util;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import org.duarteduarte.li3.data.Artigo;
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
        for (AutoresAno artsAno : ra.getAutores().values()) {
            for (Autor art : artsAno.getAutoresAno().values()) {
                aux.add(art);
            }
        }

        return aux;
    }

    public static Collection<Autor> conjuntoAutores(RedeAutores ra) {
        Collection<Autor> aux = Factories.giveMeSet();
        for (AutoresAno artsAno : ra.getAutores().values()) {
            for (Autor art : artsAno.getAutoresAno().values()) {
                if (art != null) {
                    aux.add(art);
                }
            }
        }

        return aux;
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
                toKeep.add(tmp);
            }
        }

        return toKeep;
    }
}
