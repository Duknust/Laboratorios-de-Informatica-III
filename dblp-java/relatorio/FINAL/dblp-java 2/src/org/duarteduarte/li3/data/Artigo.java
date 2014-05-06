/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3.data;

import java.io.Serializable;
import java.util.List;
import org.duarteduarte.li3.util.Factories;

/**
 *
 * @author duarteduarte
 */
public class Artigo implements Comparable, Serializable {

    private List<String> autores = null;
    private int numeroAutores = 0;

    public Artigo() {
        this.autores = Factories.giveMeList();
    }

    protected Artigo(Artigo art) {
        this.autores = Factories.giveMeList();
        this.autores.addAll(art.getAutores());
        this.numeroAutores = art.getNumeroAutores();
    }

    public int getNumeroAutores() {
        return numeroAutores;
    }

    public void setNumeroAutores(int numeroAutores) {
        this.numeroAutores = numeroAutores;
    }

    @Override
    public String toString() {
        return "Artigo{" + "autores=" + autores + '}';
    }

    public boolean insereAutor(String autor) {
        boolean res = false;
        if (res = this.autores.add(autor)) {
            this.numeroAutores++;
        }
        return res;
    }

    public boolean isSingleAuthor() {
        return numeroAutores == 1;
    }

    public boolean isWrittenByN(int n) {
        return numeroAutores == n;
    }

    public boolean isWrittenByLessThanN(int n) {
        return numeroAutores < n;
    }

    public boolean isWrittenByMoreThanN(int n) {
        return numeroAutores > n;
    }

    public List<String> getAutores() {
        return autores;
    }

    public void setAutores(List<String> autores) {
        this.autores = autores;
    }

    @Override
    public int compareTo(Object t) {
        final Artigo other = (Artigo) t;
        if (this.equals(t)) {
            return 0;
        }
        if (other.equalsListaAutores(other.getAutores())) {
            return 0;
        }
        if (other.getAutores().size() > this.autores.size()) {
            return 1;
        } else {
            return -1;
        }
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 83 * hash + (this.autores != null ? this.autores.hashCode() : 0);
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
        final Artigo other = (Artigo) obj;
        if (this.autores != other.autores && (this.autores == null || !this.equals(other.autores))) {
            return false;
        }
        return true;
    }

    private boolean equalsListaAutores(List<String> other) {
        boolean res = true;
        if (other == null && this.autores != null) {
            res = false;
        } else if (other != null && this.autores == null) {
            res = false;
        } else if (other.size() != this.autores.size()) {
            res = false;
        } else {
            for (String autor : other) {
                if (!this.autores.contains(autor)) {
                    return false;
                }
            }
        }
        return res;
    }

    @Override
    public Object clone() {
        return new Artigo(this);
    }
}
