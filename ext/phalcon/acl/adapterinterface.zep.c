
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
 * Phalcon\Acl\AdapterInterface
 *
 * Interface for Phalcon\Acl adapters
 */
ZEPHIR_INIT_CLASS(Phalcon_Acl_AdapterInterface) {

	ZEPHIR_REGISTER_INTERFACE(Phalcon\\Acl, AdapterInterface, phalcon, acl_adapterinterface, phalcon_acl_adapterinterface_method_entry);

	return SUCCESS;

}

/**
 * Sets the default access level (Phalcon\Acl::ALLOW or Phalcon\Acl::DENY)
 *
 * @param int defaultAccess
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, setDefaultAction);

/**
 * Returns the default ACL access level
 *
 * @return int
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, getDefaultAction);

/**
 * Adds a role to the ACL list. Second parameter lets to inherit access data from other existing role
 *
 * @param  Phalcon\Acl\RoleInterface role
 * @param  string accessInherits
 * @return boolean
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, addRole);

/**
 * Do a role inherit from another existing role
 *
 * @param string roleName
 * @param string roleToInherit
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, addInherit);

/**
 * Check whether role exist in the roles list
 *
 * @param  string roleName
 * @return boolean
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, isRole);

/**
 * Check whether resource exist in the resources list
 *
 * @param  string resourceName
 * @return boolean
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, isResource);

/**
 * Adds a resource to the ACL list
 *
 * Access names can be a particular action, by example
 * search, update, delete, etc or a list of them
 *
 * @param   Phalcon\Acl\ResourceInterface resource
 * @param   array accessList
 * @return  boolean
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, addResource);

/**
 * Adds access to resources
 *
 * @param string resourceName
 * @param mixed accessList
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, addResourceAccess);

/**
 * Removes an access from a resource
 *
 * @param string resourceName
 * @param mixed accessList
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, dropResourceAccess);

/**
 * Allow access to a role on a resource
 *
 * @param string roleName
 * @param string resourceName
 * @param mixed access
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, allow);

/**
 * Deny access to a role on a resource
 *
 * @param string roleName
 * @param string resourceName
 * @param mixed access
 * @return boolean
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, deny);

/**
 * Check whether a role is allowed to access an action from a resource
 *
 * @param  string role
 * @param  string resource
 * @param  string access
 * @return boolean
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, isAllowed);

/**
 * Returns the role which the list is checking if it's allowed to certain resource/access
 *
 * @return string
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, getActiveRole);

/**
 * Returns the resource which the list is checking if some role can access it
 *
 * @return string
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, getActiveResource);

/**
 * Returns the access which the list is checking if some role can access it
 *
 * @return string
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, getActiveAccess);

/**
 * Return an array with every role registered in the list
 *
 * @return Phalcon\Acl\RoleInterface[]
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, getRoles);

/**
 * Return an array with every resource registered in the list
 *
 * @return Phalcon\Acl\ResourceInterface[]
 */
ZEPHIR_DOC_METHOD(Phalcon_Acl_AdapterInterface, getResources);

