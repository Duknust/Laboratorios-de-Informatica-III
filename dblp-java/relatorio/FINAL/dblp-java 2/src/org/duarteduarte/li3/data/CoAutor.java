/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.duarteduarte.li3.data;

import java.io.Serializable;

/**
 *
 * @author duarteduarte
 */
public class CoAutor implements Serializable, Comparable {

    @Override
    public int compareTo(Object t) {
        CoAutor aux = (CoAutor) t;
        return this.nome.compareTo(aux.getNome()); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 97 * hash + (this.nome != null ? this.nome.hashCode() : 0);

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
        final CoAutor other = (CoAutor) obj;
        if ((this.nome == null) ? (other.nome != null) : !this.nome.equals(other.nome)) {
            return false;
        }

        return true;
    }
    private String nome;

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public int getArtigosComum() {
        return artigosComum;
    }

    public void setArtigosComum(int artigosComum) {
        this.artigosComum = artigosComum;
    }
    private int artigosComum = 0;

    @Override
    public Object clone() {
        return new CoAutor(this); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public String toString() {
        return "CoAutor{" + "nome=" + nome + ", artigosComum=" + artigosComum + '}';
    }

    public CoAutor(String nome) {
        this.nome = nome;
        this.artigosComum = 1;
    }

    public CoAutor() {
        this.artigosComum = 1;
    }

    public CoAutor(CoAutor other) {
        this.artigosComum = other.getArtigosComum();
        this.nome = other.getNome();
    }

    public void addCoAutorias(int coAutorias) {
        this.artigosComum += coAutorias;
    }
}
