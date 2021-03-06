
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/filter.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/concat.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Security
 *
 * This component provides a set of functions to improve the security in Phalcon applications
 *
 *<code>
 *	$login = $this->request->getPost('login');
 *	$password = $this->request->getPost('password');
 *
 *	$user = Users::findFirstByLogin($login);
 *	if ($user) {
 *		if ($this->security->checkHash($password, $user->password)) {
 *			//The password is valid
 *		}
 *	}
 *</code>
 */
ZEPHIR_INIT_CLASS(Phalcon_Security) {

	ZEPHIR_REGISTER_CLASS(Phalcon, Security, phalcon, security, phalcon_security_method_entry, 0);

	zend_declare_property_null(phalcon_security_ce, SL("_dependencyInjector"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(phalcon_security_ce, SL("_workFactor"), 8, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(phalcon_security_ce, SL("_numberBytes"), 16, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_security_ce, SL("_csrf"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(phalcon_security_ce TSRMLS_CC, 1, phalcon_di_injectionawareinterface_ce);
	return SUCCESS;

}

PHP_METHOD(Phalcon_Security, setWorkFactor) {

	zval *workFactor;

	zephir_fetch_params(0, 1, 0, &workFactor);



	zephir_update_property_this(this_ptr, SL("_workFactor"), workFactor TSRMLS_CC);

}

PHP_METHOD(Phalcon_Security, getWorkFactor) {


	RETURN_MEMBER(this_ptr, "_workFactor");

}

/**
 * Sets the dependency injector
 *
 * @param Phalcon\DiInterface $dependencyInjector
 */
PHP_METHOD(Phalcon_Security, setDI) {

	zval *dependencyInjector;

	zephir_fetch_params(0, 1, 0, &dependencyInjector);



	if (!(zephir_instance_of_ev(dependencyInjector, phalcon_diinterface_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "Parameter 'dependencyInjector' must be an instance of 'Phalcon\\DiInterface'", "", 0);
		return;
	}
	zephir_update_property_this(this_ptr, SL("_dependencyInjector"), dependencyInjector TSRMLS_CC);

}

/**
 * Returns the internal dependency injector
 *
 * @return Phalcon\DiInterface
 */
PHP_METHOD(Phalcon_Security, getDI) {


	RETURN_MEMBER(this_ptr, "_dependencyInjector");

}

/**
 * Sets a number of bytes to be generated by the openssl pseudo random generator
 *
 * @param long randomBytes
 */
PHP_METHOD(Phalcon_Security, setRandomBytes) {

	zval *randomBytes_param = NULL, *_0;
	long randomBytes;

	zephir_fetch_params(0, 1, 0, &randomBytes_param);

	if (unlikely(Z_TYPE_P(randomBytes_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'randomBytes' must be a long/integer") TSRMLS_CC);
		RETURN_NULL();
	}

	randomBytes = Z_LVAL_P(randomBytes_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, randomBytes);
	zephir_update_property_this(this_ptr, SL("_numberBytes"), _0 TSRMLS_CC);

}

/**
 * Returns a number of bytes to be generated by the openssl pseudo random generator
 *
 * @return string
 */
PHP_METHOD(Phalcon_Security, getRandomBytes) {


	RETURN_MEMBER(this_ptr, "_numberBytes");

}

/**
 * Generate a >22-length pseudo random string to be used as salt for passwords
 *
 * @return string
 */
PHP_METHOD(Phalcon_Security, getSaltBytes) {

	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *safeBytes = NULL, *numberBytes, *_0 = NULL, *_2 = NULL;

	ZEPHIR_MM_GROW();

	if (!((zephir_function_exists_ex(SS("openssl_random_pseudo_bytes") TSRMLS_CC) == SUCCESS))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_security_exception_ce, "Openssl extension must be loaded", "phalcon/security.zep", 105);
		return;
	}
	ZEPHIR_OBS_VAR(numberBytes);
	zephir_read_property_this(&numberBytes, this_ptr, SL("_numberBytes"), PH_NOISY_CC);
	while (1) {
		ZEPHIR_INIT_NVAR(safeBytes);
		ZEPHIR_CALL_FUNCTION(&_0, "openssl_random_pseudo_bytes", &_1, numberBytes);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_2, "base64_encode", &_3, _0);
		zephir_check_call_status();
		zephir_filter_alphanum(safeBytes, _2);
		if (!(zephir_is_true(safeBytes))) {
			continue;
		}
		if (zephir_fast_strlen_ev(safeBytes) < 22) {
			continue;
		}
		break;
	}
	RETURN_CCTOR(safeBytes);

}

/**
 * Creates a password hash using bcrypt with a pseudo random salt
 *
 * @param string password
 * @param int workFactor
 * @return string
 */
PHP_METHOD(Phalcon_Security, hash) {

	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL, *_7 = NULL;
	int workFactor, ZEPHIR_LAST_CALL_STATUS;
	zval *password_param = NULL, *workFactor_param = NULL, *_0, _1, _2, *_3 = NULL, *_5 = NULL, *_6;
	zval *password = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &password_param, &workFactor_param);

	zephir_get_strval(password, password_param);
	if (!workFactor_param) {
		workFactor = 0;
	} else {
		workFactor = zephir_get_intval(workFactor_param);
	}


	if (!(workFactor)) {
		ZEPHIR_OBS_VAR(_0);
		zephir_read_property_this(&_0, this_ptr, SL("_workFactor"), PH_NOISY_CC);
		workFactor = zephir_get_intval(_0);
	}
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "%02s", 0);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_LONG(&_2, workFactor);
	ZEPHIR_CALL_FUNCTION(&_3, "sprintf", &_4, &_1, &_2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, this_ptr, "getsaltbytes", NULL);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_6);
	ZEPHIR_CONCAT_SVSV(_6, "$2a$", _3, "$", _5);
	ZEPHIR_RETURN_CALL_FUNCTION("crypt", &_7, password, _6);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Checks a plain text password and its hash version to check if the password matches
 *
 * @param string password
 * @param string passwordHash
 * @param int maxPasswordLength
 * @return boolean
 */
PHP_METHOD(Phalcon_Security, checkHash) {

	unsigned char _5;
	long _4;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zend_bool _0;
	char ch;
	int maxPassLength, i, sum, cryptedLength, passwordLength, ZEPHIR_LAST_CALL_STATUS;
	zval *password_param = NULL, *passwordHash_param = NULL, *maxPassLength_param = NULL, *_1 = NULL;
	zval *password = NULL, *passwordHash = NULL, *cryptedHash = NULL, *_3 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &password_param, &passwordHash_param, &maxPassLength_param);

	zephir_get_strval(password, password_param);
	zephir_get_strval(passwordHash, passwordHash_param);
	if (!maxPassLength_param) {
		maxPassLength = 0;
	} else {
		maxPassLength = zephir_get_intval(maxPassLength_param);
	}


	if (maxPassLength) {
		_0 = maxPassLength > 0;
		if (_0) {
			_0 = zephir_fast_strlen_ev(password) > maxPassLength;
		}
		if (_0) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_CALL_FUNCTION(&_1, "crypt", &_2, password, passwordHash);
	zephir_check_call_status();
	zephir_get_strval(_3, _1);
	ZEPHIR_CPY_WRT(cryptedHash, _3);
	cryptedLength = zephir_fast_strlen_ev(cryptedHash);
	passwordLength = zephir_fast_strlen_ev(passwordHash);
	zephir_concat_self(&cryptedHash, passwordHash TSRMLS_CC);
	sum = (cryptedLength - passwordLength);
	for (_4 = 0; _4 < Z_STRLEN_P(passwordHash); _4++) {
		i = _4; 
		ch = ZEPHIR_STRING_OFFSET(passwordHash, _4);
		_5 = ZEPHIR_STRING_OFFSET(cryptedHash, i);
		sum = (sum | ((_5 ^ ch)));
	}
	RETURN_MM_BOOL(0 == sum);

}

/**
 * Checks if a password hash is a valid bcrypt's hash
 *
 * @param string password
 * @param string passwordHash
 * @return boolean
 */
PHP_METHOD(Phalcon_Security, isLegacyHash) {

	zval *password_param = NULL, *passwordHash_param = NULL;
	zval *password = NULL, *passwordHash = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &password_param, &passwordHash_param);

	zephir_get_strval(password, password_param);
	zephir_get_strval(passwordHash, passwordHash_param);


	RETURN_MM_BOOL(zephir_start_with_str(passwordHash, SL("$2a$")));

}

/**
 * Generates a pseudo random token key to be used as input's name in a CSRF check
 *
 * @param int numberBytes
 * @return string
 */
PHP_METHOD(Phalcon_Security, getTokenKey) {

	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL;
	zval *numberBytes_param = NULL, *safeBytes, *dependencyInjector = NULL, *session = NULL, *_0, *_1 = NULL, *_2 = NULL, *_3 = NULL, *_5 = NULL;
	int numberBytes, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &numberBytes_param);

	if (!numberBytes_param) {
		numberBytes = 0;
	} else {
		numberBytes = zephir_get_intval(numberBytes_param);
	}


	if (!(numberBytes)) {
		numberBytes = 12;
	}
	if (!((zephir_function_exists_ex(SS("openssl_random_pseudo_bytes") TSRMLS_CC) == SUCCESS))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_security_exception_ce, "Openssl extension must be loaded", "phalcon/security.zep", 209);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dependencyInjector"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(dependencyInjector, _0);
	if (Z_TYPE_P(dependencyInjector) != IS_OBJECT) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_security_exception_ce, "A dependency injection container is required to access the 'session' service", "phalcon/security.zep", 214);
		return;
	}
	ZEPHIR_INIT_VAR(safeBytes);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, numberBytes);
	ZEPHIR_CALL_FUNCTION(&_2, "openssl_random_pseudo_bytes", NULL, _1);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_3, "base64_encode", &_4, _2);
	zephir_check_call_status();
	zephir_filter_alphanum(safeBytes, _3);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "session", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_5, dependencyInjector, "getshared", NULL, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(session, _5);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "$PHALCON/CSRF/KEY$", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, session, "set", NULL, _1, safeBytes);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	RETURN_CCTOR(safeBytes);

}

/**
 * Generates a pseudo random token value to be used as input's value in a CSRF check
 *
 * @param int numberBytes
 * @return string
 */
PHP_METHOD(Phalcon_Security, getToken) {

	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zval *numberBytes_param = NULL, *token = NULL, *dependencyInjector = NULL, *session = NULL, *_0 = NULL, *_1 = NULL, *_3;
	int numberBytes, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &numberBytes_param);

	if (!numberBytes_param) {
		numberBytes = 0;
	} else {
		numberBytes = zephir_get_intval(numberBytes_param);
	}


	if (!(numberBytes)) {
		numberBytes = 12;
	}
	if (!((zephir_function_exists_ex(SS("openssl_random_pseudo_bytes") TSRMLS_CC) == SUCCESS))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_security_exception_ce, "Openssl extension must be loaded", "phalcon/security.zep", 239);
		return;
	}
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, numberBytes);
	ZEPHIR_CALL_FUNCTION(&token, "openssl_random_pseudo_bytes", NULL, _0);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_1, "base64_encode", &_2, token);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(token, _1);
	ZEPHIR_INIT_NVAR(_0);
	zephir_filter_alphanum(_0, token);
	ZEPHIR_CPY_WRT(token, _0);
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("_dependencyInjector"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(dependencyInjector, _3);
	if (Z_TYPE_P(dependencyInjector) != IS_OBJECT) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_security_exception_ce, "A dependency injection container is required to access the 'session' service", "phalcon/security.zep", 249);
		return;
	}
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "session", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_1, dependencyInjector, "getshared", NULL, _0);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(session, _1);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "$PHALCON/CSRF$", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, session, "set", NULL, _0, token);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_CCTOR(token);

}

/**
 * Check if the CSRF token sent in the request is the same that the current in session
 *
 * @param string tokenKey
 * @param string tokenValue
 * @return boolean
 */
PHP_METHOD(Phalcon_Security, checkToken) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *tokenKey = NULL, *tokenValue = NULL, *dependencyInjector = NULL, *session = NULL, *request = NULL, *token = NULL, *_0, *_1 = NULL, *_2 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &tokenKey, &tokenValue);

	if (!tokenKey) {
		ZEPHIR_CPY_WRT(tokenKey, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(tokenKey);
	}
	if (!tokenValue) {
		tokenValue = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dependencyInjector"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(dependencyInjector, _0);
	if (Z_TYPE_P(dependencyInjector) != IS_OBJECT) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_security_exception_ce, "A dependency injection container is required to access the 'session' service", "phalcon/security.zep", 272);
		return;
	}
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "session", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_1, dependencyInjector, "getshared", NULL, _2);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(session, _1);
	if (!(zephir_is_true(tokenKey))) {
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "$PHALCON/CSRF/KEY$", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&tokenKey, session, "get", NULL, _2);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
	}
	if (!(zephir_is_true(tokenValue))) {
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "request", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&request, dependencyInjector, "getshared", NULL, _2);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&token, request, "getpost", NULL, tokenKey);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(token, tokenValue);
	}
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_STRING(_2, "$PHALCON/CSRF$", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_1, session, "get", NULL, _2);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	RETURN_MM_BOOL(ZEPHIR_IS_EQUAL(token, _1));

}

/**
 * Returns the value of the CSRF token in session
 *
 * @return string
 */
PHP_METHOD(Phalcon_Security, getSessionToken) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *dependencyInjector = NULL, *session = NULL, *_0, *_1 = NULL, *_2 = NULL;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dependencyInjector"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(dependencyInjector, _0);
	if (Z_TYPE_P(dependencyInjector) != IS_OBJECT) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_security_exception_ce, "A dependency injection container is required to access the 'session' service", "phalcon/security.zep", 310);
		return;
	}
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "session", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_1, dependencyInjector, "getshared", NULL, _2);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(session, _1);
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_STRING(_2, "$PHALCON/CSRF$", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_METHOD(session, "get", NULL, _2);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * string \Phalcon\Security::computeHmac(string $data, string $key, string $algo, bool $raw = false)
 *
 *
 * @param string data
 * @param string key
 * @param string algo
 * @param boolean raw
 */
PHP_METHOD(Phalcon_Security, computeHmac) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *data, *key, *algo, *raw = NULL, *ops = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 1, &data, &key, &algo, &raw);

	if (!raw) {
		raw = ZEPHIR_GLOBAL(global_false);
	}


	ZEPHIR_CALL_FUNCTION(&ops, "hash_hmac", NULL, algo, data, key, raw);
	zephir_check_call_status();
	if (!(zephir_is_true(ops))) {
		ZEPHIR_INIT_VAR(_0);
		object_init_ex(_0, phalcon_security_exception_ce);
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_SV(_1, "Unknown hashing algorithm: %s", algo);
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, _1);
		zephir_check_call_status();
		zephir_throw_exception_debug(_0, "phalcon/security.zep", 332 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CCTOR(ops);

}

