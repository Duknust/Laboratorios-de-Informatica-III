/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3.data;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;

/**
 *
 * @author duarteduarte
 */
public class Autor implements Serializable, Comparable<Autor> {

    private String nome;
    private HashMap<String, CoAutor> coAutores;
    private int numCoautorias;
    private int numArtigosSolo;

    public Autor() {
        this.coAutores = new HashMap<String, CoAutor>();
        this.numCoautorias = 0;
        this.numArtigosSolo = 0;
    }

    public Autor(String nome) {
        this.nome = nome;
        this.numCoautorias = 0;
        this.numArtigosSolo = 0;
    }

    public Autor(String nome, int nArtigos, int nArtigosSolo, Collection<CoAutor> coAutores) {
        this.nome = nome;
        this.setCoAutores(coAutores);
        this.numCoautorias = nArtigos;
        this.numArtigosSolo = nArtigosSolo;
    }

    public Autor(Autor other) {
        this.nome = other.getNome();
        this.setCoAutores(other.getCoAutores());
        this.numCoautorias = other.getNumCoautorias();
        this.numArtigosSolo = other.getNumArtigosSolo();
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    @Override
    public int compareTo(Autor t) {
        return this.nome.compareTo(t.getNome()); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public String toString() {
        return "Autor{ " + this.nome + ", nCoautorias=" + this.numCoautorias + ", nArtigosSolo=" + this.numArtigosSolo + ", coAutores=" + this.coAutores + '}';
    }

    @Override
    public int hashCode() {
        int hash = 7;
        //hash = 83 * hash + (this.coAutores != null ? this.coAutores.hashCode() : 0);
        hash = 83 * hash + (this.nome != null ? this.nome.hashCode() : 0);

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
        if (!this.nome.equalsIgnoreCase(other.nome)) {
            return false;
        }

        return true;
    }

    public Collection<CoAutor> getCoAutores() {
        return coAutores.values();
    }

    public List<String> getCoAutoresNome() {
        return new ArrayList<String>(this.coAutores.keySet());
    }

    public final void setCoAutores(Collection<CoAutor> coAutores) {
        if (this.coAutores != null && !this.coAutores.isEmpty()) {
            this.coAutores.clear();
        } else {
            this.coAutores = new HashMap<String, CoAutor>();
        }

        for (CoAutor aux : coAutores) {
            this.coAutores.put(aux.getNome(), new CoAutor(aux));
        }
    }

    public int getNumCoautorias() {
        return numCoautorias;
    }

    public void setnArtigos(int nArtigos) {
        this.numCoautorias = nArtigos;
    }

    public int getNumArtigosSolo() {
        return numArtigosSolo;
    }

    public void setnArtigosSolo(int nArtigosSolo) {
        this.numArtigosSolo = nArtigosSolo;
    }

    public int getNumeroCoAutores() {
        return this.coAutores.size();
    }

    public final boolean addCoAutores(Collection<CoAutor> coautores) {
        boolean res = false;
        CoAutor coAut = null;

        for (CoAutor aux : coautores) {
            if ((coAut = this.coAutores.get(aux.getNome())) != null) {
                coAut.addCoAutorias(aux.getArtigosComum());
                res = true;
            } else {
                res = (this.coAutores.put(aux.getNome(), aux) == null);
            }
        }

        return res;
    }

    public void incrementaContadores(int nCoAutorias, int nArtigosSolo) {
        this.numCoautorias += nCoAutorias;
        this.numArtigosSolo += nArtigosSolo;
    }

    public int totalArtigos() {
        return this.numArtigosSolo + this.numCoautorias;
    }
}
