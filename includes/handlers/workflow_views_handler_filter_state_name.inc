<?php
// $Id: workflow_views_handler_filter_state_name.inc,v 1.1.2.1 2010/08/27 19:37:49 q0rban Exp $

/**
 * @file
 * Provide views filter handler for workflow.module.
 */

/**
 * Filter by state.
 */
class workflow_views_handler_filter_state_name extends views_handler_filter_in_operator {
  var $value_form_type = 'select';

  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Workflow state');

      $this->value_options = workflow_get_state_labels();;
    }
  }

  function query() {
    if (empty($this->value)) {
      return;
    }
    $this->ensure_my_table();

    // Somewhere $this->definition['numeric'] is set to TRUE but this is wrong.
    // state_name will always be a string
    // TODO Hunt down where $this->definition['numeric'] is being set
    // $placeholder = !empty($this->definition['numeric']) ? '%d' : "'%s'";
    $placeholder = "'%s'";

    if (count($this->value) == 1) {
      $this->operator = ($this->operator == 'in') ? '= ' : '!= ';
      // $in = !empty($this->definition['numeric']) ? '%d' : "'%s'";
      $in = $placeholder;
    }
    else {
      $replace = array_fill(0, sizeof($this->value), $placeholder);
      $in = ' (' . implode(", ", $replace) . ')';
    }
    $value = array_keys($this->value);
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field " . $this->operator . $in, $value);
  }
}
