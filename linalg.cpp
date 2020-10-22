/* implementation of methods for matrix and vector */

#include "linalg.hpp"

//------------------CONSTRUCTORS START --------------------

vector::vector(int a) {
    if (a > 0) {
	v_vec = std::vector < number > (a, number(0));
    } else { assert(0); }
}

vector::vector(const std::vector < number > & v): v_vec(v) {}

matrix::matrix(int cols, int rows) {
    if (cols > 0 && rows > 0) {
	m_vec = std::vector < vector > (rows, vector(cols));
    } else { assert(0); }
}

matrix::matrix(const std::vector < vector > & v): m_vec(v) {}

//------------------CONSTRUCTORS END ----------------------

vector operator + (const vector & v1,
    const vector & v2) {
    std::vector < number > rv;

    if (v1.v_vec.size() != v2.v_vec.size()) {
        assert(0);
    }
    for (unsigned i = 0; i < v1.v_vec.size(); i++) {
        rv.push_back((v1.v_vec[i] + v2.v_vec[i]));
    }

    vector result = vector(rv);
    return result;
}

vector operator - (const vector & v1,
    const vector & v2) {
    std::vector < number > rv;
    if (v1.v_vec.size() != v2.v_vec.size()) {
        assert(0);
    }
    for (unsigned i = 0; i < v1.v_vec.size(); i++) {
        rv.push_back((v1.v_vec[i] - v2.v_vec[i]));
    }

    vector result = vector(rv);
    return result;
}

vector operator * (const vector & v,
    const number & n) {
    std::vector < number > rv;
    for (const auto & i : v.v_vec) {
        rv.push_back(i * n);
    }
    vector result = vector(rv);
    return result;
}

vector operator * (const number & n,
    const vector & v) {
    return (operator * (v, n));
}

number vector::operator * (const vector & v2) const {
    number res = 0;
    if (v_vec.size() != v2.v_vec.size()) {
        assert(0);
    }

    for (unsigned i = 0; i < v_vec.size(); i++) {
        res = (res + (v_vec[i] * v2.v_vec[i]));
    }
    return res;
}

matrix operator + (const matrix & m1,
    const matrix & m2) {
    unsigned cols = 0;
    unsigned rows = 0;

    if (!m1.m_vec.empty() && !m2.m_vec.empty()) {
	if (!m1.m_vec[0].v_vec.empty() && !m2.m_vec[0].v_vec.empty()) {
	    if (m1.m_vec.size() == m2.m_vec.size() &&
		    m1.m_vec[0].v_vec.size() == m2.m_vec[0].v_vec.size()) {
		rows = m1.m_vec.size();
		cols = m1.m_vec[0].v_vec.size();
	    } else { assert(0); }
	} else { assert(0); }    
    } else { assert(0); }

    std::vector < vector > rv(rows, vector(cols));

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            rv[i].v_vec[j] = (m1.m_vec[i].v_vec[j] + m2.m_vec[i].v_vec[j]);
        }
    }

    matrix result = matrix(rv);
    return result;
}

vector operator * (const vector & v,
    const matrix & m) {
    if (m.m_vec.empty() || v.v_vec.empty() ||
	    (m.m_vec.size() != v.v_vec.size())) {
        assert(0);
    }
    unsigned rows = m.m_vec.size();
    unsigned cols = m.m_vec[0].v_vec.size();
    vector res = vector(cols);

    for (unsigned i = 0; i < cols; i++) {
        for (unsigned j = 0; j < rows; j++) {
            res.v_vec[i] = (res.v_vec[i] + (m.m_vec[j].v_vec[i] * v.v_vec[j]));
        }
    }

    return res;
}

vector operator * (const matrix & m,
    const vector & v) {
    if(m.m_vec.empty() || v.v_vec.empty() || (
		m.m_vec[0].v_vec.size() != v.v_vec.size())) {
	assert(0);
    }
    unsigned rows = m.m_vec.size();
    unsigned cols = v.v_vec.size();
    vector res = vector(rows);
    for(unsigned i = 0; i < rows; i++) {
	for (unsigned j = 0; j < cols; j++) {
	    res.v_vec[i] = res.v_vec[i] + (m.m_vec[i].v_vec[j] * v.v_vec[j]);
	}
    }
    return res;
}

bool operator == (const vector & v1,
    const vector & v2) {
    if (v1.v_vec.size() != v2.v_vec.size()) {
        return false;
    }

    for (unsigned i = 0; i < v1.v_vec.size(); i++) {
        if (v1.v_vec[i] != v2.v_vec[i]) {
            return false;
        }
    }

    return true;
}

bool operator != (const vector & v1,
    const vector & v2) {
    return !(v1 == v2);
}

bool operator == (const matrix & m1,
    const matrix & m2) {
    if (m1.m_vec.size() != m2.m_vec.size()) {
        return false;
    }

    for (unsigned i = 0; i < m1.m_vec.size(); i++) {
        if (m1.m_vec[i] != m2.m_vec[i]) {
            return false;
        }
    }

    return true;
}

bool operator != (const matrix & m1,
    const matrix & m2) {
    return !(m1 == m2);
}

vector matrix::row(int n) const {
    if (n < 0 || (n >= static_cast < int > (m_vec.size()))) {
        assert(0);
    }

    vector res = m_vec[n];
    return res;
}

vector matrix::col(int n) const {
    if (n < 0 || (!m_vec.empty() && static_cast < int > (m_vec[0].v_vec.size()) <= n)) {
        assert(0);
    }

    vector res = vector(static_cast < int > (m_vec.size()));
    for (unsigned i = 0; i < m_vec.size(); i++) {
        res.v_vec[i] = m_vec[i].v_vec[n];
    }

    return res;
}

void matrix::gauss() {
    if (m_vec.empty()) { return; }
    unsigned lead = 0;
    unsigned rowCount = m_vec.size();
    unsigned colCount = m_vec[0].v_vec.size();
    unsigned i = 0;
    number lv;
    unsigned rv = 0;
    for (unsigned r = 0; r < rowCount; r++) {
        if (lead >= colCount) {
            return;
        }
        i = r;
        while (m_vec[i].v_vec[lead] == 0) {
            i++;
            if (i == rowCount) {
                i = r;
                lead++;
                if (lead == colCount) {
                    return;
                }
            }
        }

        std::swap(m_vec[i], m_vec[r]);
        lv = m_vec[r].v_vec[lead];
        for (auto & mrx: m_vec[r].v_vec) {
            mrx = (mrx / lv);
        }

        for (unsigned z = 0; z < rowCount; z++) {
            if (z != r) {
                lv = m_vec[z].v_vec[lead];
                rv = 0;
                for (auto & mrx: m_vec[z].v_vec) {
                    mrx = (mrx - (lv * m_vec[r].v_vec[rv]));
                    rv++;
                }
            }
        }

        lead++;
    }
}

int matrix::rank() const {
    unsigned n = m_vec.size();
    unsigned m = 0;
    if (!m_vec.empty() && !m_vec[0].v_vec.empty()) {
        m = m_vec[0].v_vec.size();
    } else {
        assert(0);
    }
    std::vector < vector > copy_vec = m_vec;

    int rank = 0;
    std::vector < bool > row_selected(n, false);
    for (unsigned i = 0; i < m; i++) {
        unsigned j;
        for (j = 0; j < n; j++) {
            if (!row_selected[j] && (copy_vec[j].v_vec[i] != 0)) {
                break;
            }
        }
        if (j != n) {
            rank++;
            row_selected[j] = true;
            for (unsigned p = i + 1; p < m; p++) {
                copy_vec[j].v_vec[p] = (copy_vec[j].v_vec[p] / copy_vec[j].v_vec[i]);
            }
            for (unsigned k = 0; k < n; k++) {
                if (k != j && (copy_vec[k].v_vec[i] != 0)) {
                    for (unsigned p = i + 1; p < m; p++) {
                        copy_vec[k].v_vec[p] = (copy_vec[k].v_vec[p] -
                            (copy_vec[j].v_vec[p] * copy_vec[k].v_vec[i]));
                    }
                }
            }
        }
    }

    return rank;
}

number matrix::det() const {
    unsigned n = m_vec.size();
    unsigned m = 0;
    if (!m_vec.empty() && !m_vec[0].v_vec.empty()) {
        m = m_vec[0].v_vec.size();
    } else {
        assert(0);
    }
    
    if (n <= 0 || n != m) {
        assert(0);
    }

    std::vector < vector > mat = m_vec;
    for (unsigned i = 0; i < n; i++) {
	if (mat[i].v_vec[i] == 0) {
	    unsigned o = i + 1;
	    while (o < n && mat[o].v_vec[i] == 0) {
		o++;
	    }
	    if (o < n) { std::swap(mat[i], mat[o]); }
	}

	for (unsigned j = 0; j < n; j++) {
	    if (j > i) {
		number c = mat[j].v_vec[i]/mat[i].v_vec[i];
		for (unsigned k = i; k < n; k++) {
		    mat[j].v_vec[k] = mat[j].v_vec[k] - (c * mat[i].v_vec[k]);
		} 
		
	    }
	}
    
    }

    number result = 1;
    for (unsigned i = 0; i < n; i++) {
	result = result * (mat[i].v_vec[i]);	
    }
    return result;
}

matrix matrix::inv() const {
    unsigned r = 0;
    unsigned c = 0;
    if (!m_vec.empty() && !m_vec[0].v_vec.empty()) {
	r = m_vec.size();
	c = m_vec[0].v_vec.size();
    }
    if (r == 0 || c == 0 || (r != c)) { assert(0); }

    matrix mcopy = matrix(c * 2, r);
 
    // augmented matrix copy
    for(unsigned i = 0; i < r; i++) {
	for(unsigned j = 0; j < c; j++) {
	    mcopy.m_vec[i].v_vec[j] = m_vec[i].v_vec[j];
	    if (j + c == (i + c)) {
		mcopy.m_vec[i].v_vec[j+c] = 1;
	    }
	}
    }
    
    mcopy.gauss();
    matrix result = matrix(c, r);
    for (unsigned i = 0; i < r; i++) {
	for (unsigned j = r, col = 0; j < 2 * c; j++, col++) {
	    result.m_vec[i].v_vec[col] = mcopy.m_vec[i].v_vec[j];
	}
    }

    return result;
}

