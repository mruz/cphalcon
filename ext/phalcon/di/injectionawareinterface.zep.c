
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


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
 * Phalcon\Di\InjectionAwareInterface
 *
 * This interface must be implemented in those classes that uses internally the Phalcon\Di that creates them
 */
ZEPHIR_INIT_CLASS(Phalcon_Di_InjectionAwareInterface) {

	ZEPHIR_REGISTER_INTERFACE(Phalcon\\Di, InjectionAwareInterface, phalcon, di_injectionawareinterface, phalcon_di_injectionawareinterface_method_entry);

	return SUCCESS;

}

/**
 * Sets the dependency injector
 *
 * @param Phalcon\DiInterface dependencyInjector
 */
ZEPHIR_DOC_METHOD(Phalcon_Di_InjectionAwareInterface, setDI);

/**
 * Returns the internal dependency injector
 *
 * @return Phalcon\DiInterface
 */
ZEPHIR_DOC_METHOD(Phalcon_Di_InjectionAwareInterface, getDI);

