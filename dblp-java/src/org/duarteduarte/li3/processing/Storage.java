/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3.processing;

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
        boolean res = false;
        CoAutor tmp=null;
        
        this.redeAutores.addAutoresArtigo(artigo.getNumeroAutores());
        
        AutoresAno aux = redeAutores.getAutoresAno(ano);
        if (aux == null) {
            aux = new AutoresAno();
        }

        List<CoAutor> coautores = Factories.giveMeList();
        for (String autor : artigo.getAutores()) {
            tmp =new CoAutor(autor);
            tmp.addCoAutoria();
            coautores.add(tmp);
        }

        for (String autor : artigo.getAutores()) {
            Autor a = new Autor(autor, coautores.size() > 1 ? 1 : 0, coautores.size() <= 1 ? 1 : 0, Util.everythingButCoautor(autor, coautores));
            res |= aux.insereAutor(a);
        }

        redeAutores.insereAutoresAno(ano, aux);
        aux.incrementaArtigos();

        return res;
    }

    public void setFileName(String fileName) {
        this.redeAutores.setNomeFicheiro(fileName);
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
