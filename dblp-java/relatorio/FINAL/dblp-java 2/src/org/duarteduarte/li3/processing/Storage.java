/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3.processing;

import java.util.Collection;
import java.util.List;
import org.duarteduarte.li3.data.Artigo;
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
public class Storage {

    private RedeAutores redeAutores = new RedeAutores();

    public RedeAutores getRedeAutores() {
        return redeAutores;
    }

    public void setAutoresMap(RedeAutores ra) {
        this.redeAutores = ra;
    }

    public AutoresAno getArtigosAno(int ano) {
        return redeAutores.getAutoresAno(ano);
    }

    public boolean addArtigo(int ano, Artigo artigo) {
        boolean res = false, insertAtEnd = false;
        CoAutor tmp = null;
        Collection<CoAutor> everythingBut = null;
        Autor a;

        this.redeAutores.addAutoresArtigo(artigo.getNumeroAutores()); // incrementa numero total de autores

        AutoresAno aux = this.redeAutores.getAutoresAno(ano);
        if (aux == null) {
            aux = new AutoresAno(ano);
            insertAtEnd = true;
        }

        List<CoAutor> coautores = Factories.giveMeList();
        for (String autor : artigo.getAutores()) {
            tmp = new CoAutor(autor);
            coautores.add(tmp);
        }

        for (String autor : artigo.getAutores()) {
            everythingBut = Util.everythingButCoautor(autor, coautores);
            a = new Autor(autor, !everythingBut.isEmpty() ? 1 : 0, everythingBut.isEmpty() ? 1 : 0, everythingBut);
            res |= aux.insereAutor(a);
        }

        aux.incrementaArtigos();

        if (insertAtEnd) {
            this.redeAutores.insereAutoresAno(ano, aux);
        }

        return res;
    }

    public void setFileName(String fileName) {
        this.redeAutores.setNomeFicheiro(fileName);
    }
    
    
    public String getFileName() {
        return this.redeAutores.getNomeFicheiro();
    }

    /*public void testAutores() {
     Artigo tmp = null, tmp2 = null;

     tmp = new Artigo();
     tmp.insereAutor(new Autor("nelson"));
     tmp.insereAutor(new Autor("ze"));

     this.addArtigo(2001, tmp);

     tmp2 = new Artigo();
     tmp2.insereAutor(new Autor("igor"));
     tmp2.insereAutor(new Autor("cardozo"));

     this.addArtigo(2013, tmp2);
     }*/
}
