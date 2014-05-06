/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3.data;

import java.io.Serializable;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import org.duarteduarte.li3.util.Factories;

/**
 *
 * @author duarteduarte
 */
public class Autor implements Serializable, Comparable<Autor> {

    private String nome;
    private Set<CoAutor> coAutores;
    private int nArtigos;
    private int nArtigosSolo;

    public Autor() {
        this.coAutores = Factories.giveMeSet();
        this.nArtigos = 0;
        this.nArtigosSolo = 0;
    }

    public Autor(String nome, int nArtigos, int nArtigosSolo, Collection<CoAutor> coAutores) {
        this();
        this.nome = nome;
        this.coAutores.addAll(coAutores);
        if (coAutores.size() > 1) {
            for (Iterator<CoAutor> it = this.coAutores.iterator(); it.hasNext();) {
                it.next().addCoAutoria();
            }
        }
        this.nArtigos = nArtigos;
        this.nArtigosSolo = nArtigosSolo;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public Set<CoAutor> getCoAutores() {
        return coAutores;
    }

    public void setCoAutores(Set<CoAutor> coAutores) {
        this.coAutores.clear();
        this.coAutores.addAll(coAutores);
    }

    public int getNumCoautorias() {
        return nArtigos;
    }

    public void setnArtigos(int nArtigos) {
        this.nArtigos = nArtigos;
    }

    public int getnArtigosSolo() {
        return nArtigosSolo;
    }

    public void setnArtigosSolo(int nArtigosSolo) {
        this.nArtigosSolo = nArtigosSolo;
    }

    public int getNumeroCoAutores() {
        return this.coAutores.size();
    }

    @Override
    public String toString() {
        return "Autor{" + "coAutores=" + this.coAutores + ", nArtigos=" + this.nArtigos + ", nArtigosSolo=" + this.nArtigosSolo + '}';
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 83 * hash + (this.coAutores != null ? this.coAutores.hashCode() : 0);
        hash = 83 * hash + this.nArtigos;
        hash = 83 * hash + this.nArtigosSolo;
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Autor other = (Autor) obj;
        if (this.coAutores != other.coAutores && (this.coAutores == null || !this.coAutores.equals(other.coAutores))) {
            return false;
        }
        if (this.nArtigos != other.nArtigos) {
            return false;
        }
        if (this.nArtigosSolo != other.nArtigosSolo) {
            return false;
        }
        return true;
    }

    public boolean addCoAutores(Set<CoAutor> coautores) {
        Iterator<CoAutor> it = null;
        boolean res = false;

        for (it = coautores.iterator(); it.hasNext();) {
            CoAutor aux = it.next();

            if (this.coAutores.contains(aux)) {
                Iterator<CoAutor> coAutIt = this.coAutores.iterator();
                while (coAutIt.hasNext()) {
                    CoAutor coAutTmp = coAutIt.next();
                    if (coAutTmp.equals(aux) && !coAutTmp.getNome().equals(this.nome)) {
                        CoAutor x = (CoAutor) aux.clone();
                        x.addCoAutoria();
                        this.coAutores.add(aux);
                        res = true;
                    }
                }
            } else {
                res = this.coAutores.add(aux);
            }
        }

        return res;
    }

    public void incrementaContadores(int nCoAutorias, int nArtigosSolo) {
        this.nArtigos += nCoAutorias;
        this.nArtigosSolo += nArtigosSolo;
    }

    @Override
    public int compareTo(Autor t) {
        return this.nome.compareTo(t.getNome()); //To change body of generated methods, choose Tools | Templates.
    }
}